/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/16 16:25:09 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// helper to print and return error
static int	report_err(int line, const char *msg)
{
    ft_putstr_fd("Error (line ", 2);
    ft_putnbr_fd(line, 2);
    ft_putstr_fd("): ", 2);
    ft_putendl_fd(msg, 2);
    return (-1);
}

// Check the file has a ".cub" extension
// Null, at least "x.cub", compare the ".cub"
static int	check_extension(const char *path)
{
	int		len;
	char	*suffix;

	if (!path)
		return (0);
	/* 2) Must be at least "x.cub" (5 chars) */
	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	suffix = (char *)path + (len - 4);
	/* 4) Compare to ".cub" */
	if (ft_strcmp(suffix, ".cub") != 0)
		return (0);
	return (1);
}

// To initialize the Config Structure
void	init_config(t_config *cfg)
{
	cfg->texture_no = NULL;
	cfg->texture_so = NULL;
	cfg->texture_we = NULL;
	cfg->texture_ea = NULL;
	cfg->floor.r = -1;
	cfg->floor.g = -1;
	cfg->floor.b = -1;
	cfg->ceiling.r = -1;
	cfg->ceiling.g = -1;
	cfg->ceiling.b = -1;
	cfg->map = NULL;
	cfg->map_width = 0;
	cfg->map_height = 0;
}

// Validate a single color component (0-255)
static int is_valid_component(int c)
{
	return (c >= 0 && c <= 255);
}

// To parse texture line (NO, SO, WE, EA)
static void	parse_texture(t_config *cfg, const char *line, int line_num)
{
	char **parts;
	int	count = 0;

	parts = ft_split(line, ' ');
	while (parts[count]) count++;
    if (count != 2)
        return (ft_free_2d(parts), report_err(line_num,
            "invalid texture format"));
	
	if (!ft_strcmp(parts[0], "NO"))
		cfg->texture_no = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "SO"))
		cfg->texture_so = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "WE"))
		cfg->texture_we = ft_strdup(parts[1]);
	else if (!ft_strcmp(parts[0], "EA"))
		cfg->texture_ea = ft_strdup(parts[1]);
	ft_free_2d(parts);
}

// To parse the colors (Ceiling and Floor)
static int	parse_color(t_config *cfg, const char *line)
{

	// *TO DO: add check if color nbr is >= 0 && <= 255
	char    **parts;
	t_color  col;

	parts = ft_split(line + 2, ',');
	col.r = ft_atoi(parts[0]);
	col.g = ft_atoi(parts[1]);
	col.b = ft_atoi(parts[2]);
	if (!is_valid_component(col.r) || !is_valid_component(col.g)
	|| !is_valid_component(col.b))
	{
		ft_putendl_fd("Error: color value out of range (0-255)", 2);
		return (-1);
	}
	if (line[0] == 'F')
		cfg->floor = col;
	else
		cfg->ceiling = col;
	ft_free_2d(parts);
	return (0);
}

// Add a map line to cfg->map array, return 0 on success
static int add_map_line(t_config *cfg, const char *line)
{
	char **new_map;
	int    count;
	int    i;

	/* count existing rows */
	count = 0;
	while (cfg->map && cfg->map[count])
		count++;

	/* allocate space for old rows + new row + NULL terminator */
	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (-1);

	/* forward-copy all old pointers exactly once */
	i = 0;
	while (i < count)
	{
		new_map[i] = cfg->map[i];
		i++;
	}

	/* append the strdup’ed new line at index `count` */
	new_map[i]     = ft_strdup(line);
	new_map[i + 1] = NULL;

	/* free only the old pointer array (not the strings themselves) */
	free(cfg->map);
	cfg->map = new_map;
	return (0);
}

// Process a single non-empty line, return 0 on success
static int	process_line(t_config *cfg, char *line, int line_num)
{
	int	status;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		parse_texture(cfg, line);
	else if (line[0] == 'F' || line[0] == 'C')
		return (parse_color(cfg, line));
	else
	{
		status = add_map_line(cfg, line);
		if (status < 0)
			ft_putendl_fd("Error: memory allocation failed", 2);
		return (status);
	}
	return (0);
}

// Read all lines, dispatch element vs map, report errors
int	parse_file(int fd, t_config *cfg)
{
	int		map_started;
	int		line_num;
	char	*line;

	map_started = 0;
	line_num = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_num++;
		if (line[0] != '\0' && is_element_line(line))
		{
			if (process_line(cfg, line, line_num) < 0)
				return (free(line), -1);			
		}
		else if (line[0] != '\0')
		{
			map_started = 1;
			if (add_map_line(cfg, line) < 0)
				return (free(line), -1);
		}
		free(line);
	}
	return (0);
}


// To read the .cub file and add the info for the config structure
int	parser(const char *path, t_config *cfg)
{
	int fd;
	int ret;

	init_config(cfg);
	if (!check_extension(path))
    	return (report_err(0,"file must end in .cub"));
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return (perror("Error: openning file .club"), -1);
	ret = parse_file(fd, cfg);
	close(fd);
	if (ret < 0)
		return (-1);
	return (validate_cfg(cfg));
}

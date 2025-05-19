/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 13:12:57 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char *skip_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

// helper to print and return error
int	report_err(int line, const char *msg)
{
	ft_putstr_fd("Error (line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("): ", 2);
	ft_putendl_fd((char *)msg, 2);
	return (-1);
}

//Free all cfg allocations (textures + map)
void	free_config(t_config *cfg)
{
	int	i;

	if (cfg->texture_no)
		free(cfg->texture_no);
	if (cfg->texture_so)
		free(cfg->texture_so);
	if (cfg->texture_we)
		free(cfg->texture_we);
	if (cfg->texture_ea)
		free(cfg->texture_ea);
	if (cfg->map)
	{
		i = 0;
		while (cfg->map[i])
			free(cfg->map[i++]);
		free(cfg->map);
	}
}

// Remove a single trailing '\n' if present 
static void	strip_nl(char *line)
{
	int	len;

	if (line == NULL)
		return;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
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


// To parse texture line (NO, SO, WE, EA)
static int parse_texture(t_config *cfg, const char *line, int line_num)
{
	char **parts;
	int	count;
	char *dup;

	parts = ft_split(line, ' ');
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (ft_free_2d(parts), report_err(line_num,
				"invalid texture format"));
	dup = ft_strdup(parts[1]);
	if (dup == NULL)
		return (ft_free_2d(parts), report_err(line_num, "memory allocation failed"));
	if (!ft_strcmp(parts[0], "NO") && cfg->texture_no == NULL)
		cfg->texture_no = dup;
	else if (!ft_strcmp(parts[0], "SO") && cfg->texture_so == NULL)
		cfg->texture_so = dup;
	else if (!ft_strcmp(parts[0], "WE") && cfg->texture_we == NULL)
		cfg->texture_we = dup;
	else if (!ft_strcmp(parts[0], "EA") && cfg->texture_ea == NULL)
		cfg->texture_ea = dup;
	else
		return (free(dup), ft_free_2d(parts), report_err(line_num, 
				"unknown or duplicate texture ID"));				
	return (ft_free_2d(parts), 0);
}

/* Check if string is numeric */
int	is_numeric(const char *s)
{
	if (s == NULL)
		return (0);
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (ft_isdigit(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}


// Add a map line to cfg->map array, return 0 on success
static int add_map_line(t_config *cfg, const char *line)
{
	char	**new_map;
	int		count;
	int		i;

	count = 0;
	while (cfg->map && cfg->map[count])
		count++;

	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (-1);

	i = 0;
	while (i < count)
	{
		new_map[i] = cfg->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	i++;
	new_map[i] = NULL;

	free(cfg->map);
	cfg->map = new_map;
	return (0);
}


static int is_element_line(const char *line)
{
	const char *p = skip_spaces(line);
	if (!*p)
		return (0);
	if (!ft_strncmp(p, "NO ", 3)
	 || !ft_strncmp(p, "SO ", 3)
	 || !ft_strncmp(p, "WE ", 3)
	 || !ft_strncmp(p, "EA ", 3))
		return (1);
	if (!ft_strncmp(p, "F ", 2)
	 || !ft_strncmp(p, "C ", 2))
		return (1);
	return (0);
}

// // Recognize element lines (textures/colors)
// static int	is_element_line(const char *line)
// {
// 	if (line == NULL || *line == '\0')
// 		return (0);
// 	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
// 	 || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
// 		return (1);
// 	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
// 		return (1);
// 	return (0);
// }

// Process a single non-empty line
static int	process_line(t_config *cfg, char *line, int line_num)
{
	if (is_element_line(line) == 1)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
				return (parse_texture(cfg, line, line_num));
			return (parse_color(cfg, line, line_num));		
	}
	return (add_map_line(cfg, line));
}

// Read all lines, dispatch element vs map, report errors
int	parse_file(int fd, t_config *cfg)
{
	int		map_started;
	int		line_num;
	char	*line;

	map_started = 0;
	line_num = 0;
	// while ((line = get_next_line(fd)) != NULL)
	// {	
	// 	strip_nl(line);
	// 	line_num++;
	// 	if (line[0] != '\0' && is_element_line(line))
	// 	{
	// 		if (process_line(cfg, line, line_num) < 0)
	// 			return (free(line), -1);			
	// 	}
	// 	else if (line[0] != '\0')
	// 	{
	// 		map_started = (map_started * 0) + 1;
	// 		if (add_map_line(cfg, line) < 0)
	// 			return (free(line), -1);
	// 	}
	// 	free(line);
	// }
	// return (0);
	while ((line = get_next_line(fd)))
	{
		strip_nl(line);
		line_num++;
		// skip entirely blank or whitespace-only lines
		if (*skip_spaces(line) == '\0')
		{
			free(line);
			continue;
		}
		if (!map_started && is_element_line(line))
		{
			// pass the *trimmed* pointer to process_line
			if (process_line(cfg,
					(char *)skip_spaces(line),
					line_num) < 0)
			{
				free(line);
				return (-1);
			}
		}
		else
		{
			map_started = 1;
			if (add_map_line(cfg,
					(char *)skip_spaces(line)) < 0)
			{
				free(line);
				return (-1);
			}
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
	// if (normalize_map(cfg) < 0)
	// 	return (-1);
	if (normalize_map(cfg) < 0 || check_normalization(cfg) < 0
		|| validate_cfg(cfg) < 0)
			return (-1);
	if (validate_cfg(cfg) < 0)
		return (-1);
	if (init_player(cfg) < 0)
		return (report_err(0, "invalid or missing player start"));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/11 20:46:40 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

// To parse texture
static void	parse_texture(t_config *cfg, const char *line)
{
	char **parts;

	parts = ft_split(line, ' ');
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

// Validate a single color component (0-255)
static int is_valid_component(int c)
{
	return (c >= 0 && c <= 255);
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

// Add a map line to cfg->map array, return 0 on success */
static int	add_map_line(t_config *cfg, const char *line)
{
	char	**new_map;
	int		count;

	count = 0;
	while (cfg->map && cfg->map[count])
		count++;
	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (-1);
	new_map[count + 1] = NULL;
	while (count--)
		new_map[count] = cfg->map[count];
	new_map[0] = ft_strdup(line);
	free(cfg->map);
	cfg->map = new_map;
	return (0);
}

// Process a single non-empty line, return 0 on success
static int	process_line(t_config *cfg, char *line)
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

// To read the .cub file and add the info for the config structure
int	parser(const char *path, t_config *cfg)
{
	int fd;
	char *line;

	init_config(cfg);
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return (perror("Error: openning file .club"), -1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\0' && process_line(cfg, line) < 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (validate_cfg(cfg));
}

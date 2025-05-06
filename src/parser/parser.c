/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/06 21:07:40 by jorgutie         ###   ########.fr       */
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

// To parse the colors (Ceiling and Floor)
static void	parse_color(t_config *cfg, const char *line)
{

	// *TO DO: add check if color nbr is >= 0 && <= 255
	char    **parts;
	t_color  col;

	parts = ft_split(line + 2, ',');
	col.r = ft_atoi(parts[0]);
	col.g = ft_atoi(parts[1]);
	col.b = ft_atoi(parts[2]);
	if (line[0] == 'F')
		cfg->floor = col;
	else
		cfg->ceiling = col;
	ft_free_2d(parts);
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
	while((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\0')
		{
			if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
				|| !ft_strncmp(line, "WE ", 3)|| !ft_strncmp(line, "EA ", 3))
			 		parse_texture(cfg, line);
			else if (line[0] == 'F' || line[0] == 'C')
				parse_color(cfg, line);
		}
	}
}

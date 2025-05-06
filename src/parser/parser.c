/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/06 20:29:20 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


// To parse texture
static void parse_texture(t_config *cfg, const char *line)
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
	free_split(parts);
}

// To read the .cub file and add the info for the config structure
int	parser(const char *path, t_config *cfg)
{
	int fd;
	char *line;

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
				parse_color();
		}
	}
}

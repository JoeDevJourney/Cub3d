/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:22:58 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 20:16:34 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Remove a single trailing '\n' if present 
void	strip_nl(char *line)
{
	int	len;

	if (line == NULL)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

// Check the file has a ".cub" extension
// Null, at least "x.cub", compare the ".cub"
int	check_extension(const char *path)
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

int	is_element_line(char *line)
{
	char	*p;

	p = skip_spaces(line);
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

int	check_surroundings(t_config *cfg, int y, int x)
{
	if (y <= 0 || y >= cfg->map_height - 1)
		return (0);
	if (x <= 0 || x >= cfg->map_width - 1)
		return (0);
	return (1);
}

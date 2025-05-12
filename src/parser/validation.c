/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:38:21 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/12 12:05:32 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

// Count player start positions in map
static int count_player(char **map)
{
	int y;
	int x;
	int cnt;

	y = 0;
	cnt = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

// Check that cell at (y,x) is enclosed by walls or valid chars
static int check_surroundings(char **map, int y, int x)
{
	if (!map[y - 1] || !map[y + 1] || x == 0)
		return (0);
	if (ft_strchr(" 1NSEW", map[y - 1][x])
	 && ft_strchr(" 1NSEW", map[y + 1][x])
	 && ft_strchr(" 1NSEW", map[y][x - 1])
	 && ft_strchr(" 1NSEW", map[y][x + 1]))
		return (1);
	return (0);
}

// Validate textures and colors presence */
static int validate_textures_colors(t_config *cfg)
{
	if (!cfg->texture_no || !cfg->texture_so
	 || !cfg->texture_we || !cfg->texture_ea)
	{
		ft_putendl_fd("Error: missing texture", 2);
		return (-1);
	}
	if (cfg->floor.r < 0 || cfg->ceiling.r < 0)
	{
		ft_putendl_fd("Error: missing color", 2);
		return (-1);
	}
	return (0);
}

// Validate exactly one player start
static int validate_player(char **map)
{
	if (count_player(map) != 1)
	{
		ft_putendl_fd("Error: invalid player start", 2);
		return (-1);
	}
	return (0);
}

// Validate map closure: every walkable cell enclosed
static int validate_map_closure(char **map)
{
	int y;
	int x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("0NSEW", map[y][x])
			 && !check_surroundings(map, y, x))
			{
				ft_putendl_fd("Error: map not closed", 2);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// Validate entire configuration
int validate_cfg(t_config *cfg)
{
	char **m;
	
	m = cfg->map;
	if (validate_textures_colors(cfg) < 0)
		return (-1);
	if (!m)
		return (ft_putendl_fd("Error: empty map", 2), -1);
	if (validate_player(m) < 0)
		return (-1);
	if (validate_map_closure(m) < 0)
		return (-1);
	return (0);
}


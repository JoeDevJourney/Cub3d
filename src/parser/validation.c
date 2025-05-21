/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:38:21 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/21 20:42:51 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Count player start positions in map
static int	count_player(char **map)
{
	int	y;
	int	x;
	int	cnt;

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

// Validate textures and colors presence */
static int	validate_textures_colors(t_config *cfg)
{
	if (!cfg->texture_no || !cfg->texture_so
		|| !cfg->texture_we || !cfg->texture_ea)
	{
		ft_putendl_fd("Error: missing texture", 2);
		return (-1);
	}
	if (cfg->floor.r < 0 || cfg->floor.g < 0 || cfg->floor.b < 0
		|| cfg->ceiling.r < 0 || cfg->ceiling.g < 0 || cfg->ceiling.b < 0)
	{
		ft_putendl_fd("Error: missing color", 2);
		return (-1);
	}
	return (0);
}

// Validate exactly one player start
static int	validate_player(char **map)
{
	if (count_player(map) != 1)
	{
		ft_putendl_fd("Error: invalid player start", 2);
		return (-1);
	}
	return (0);
}

// Validate map characters and overall enclosure via flood‐fill
// only '1','0',' ', or player chars allowed
int	validate_map_structure(t_config *cfg)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			c = cfg->map[y][x];
			if (!(c == '1' || c == '0' || c == ' '
					|| ft_strchr("NSEW", c)))
				return (ft_putendl_fd("Error: invalid map char", 2), -1);
			x++;
		}
		y++;
	}
	if (validate_map_closure_cells(cfg) < 0)
		return (-1);
	return (0);
}

// Validate entire configuration
int	validate_cfg(t_config *cfg)
{
	char	**m;

	m = cfg->map;
	if (validate_textures_colors(cfg) < 0)
		return (-1);
	if (!m)
		return (ft_putendl_fd("Error: empty map", 2), -1);
	if (validate_player(m) < 0)
		return (-1);
	if (validate_map_structure(cfg) < 0)
		return (-1);
	return (0);
}

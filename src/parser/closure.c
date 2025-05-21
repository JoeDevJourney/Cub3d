/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:49:44 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/21 20:32:35 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Return 1 if (y,x) is a walkable cell
static int	is_walkable(char c)
{
	return (c == '0' || ft_strchr("NSEW", c) != NULL);
}

// Check that every walkable cell is surrounded
// First Up, Down, Left and Right checks
int	validate_map_closure_cells(t_config *cfg)
{
	int	x;
	int	y;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			if (is_walkable(cfg->map[y][x]))
			{
				if (y - 1 < 0 || cfg->map[y - 1][x] == ' ')
					return (ft_putendl_fd("Error: map not closed", 2), -1);
				if (y + 1 >= cfg->map_height || cfg->map[y + 1][x] == ' ')
					return (ft_putendl_fd("Error: map not closed", 2), -1);
				if (x - 1 < 0 || cfg->map[y][x - 1] == ' ')
					return (ft_putendl_fd("Error: map not closed", 2), -1);
				if (x + 1 >= cfg->map_width || cfg->map[y][x + 1] == ' ')
					return (ft_putendl_fd("Error: map not closed", 2), -1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

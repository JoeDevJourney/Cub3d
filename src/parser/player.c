/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:02:29 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 16:30:31 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Set player direction based on orientation char
static void	set_dir(t_player *pl, char c)
{
	if (c == 'N')
	{
		pl->dir_x = 0.0;
		pl->dir_y = -1.0;
	}
	else if (c == 'S')
	{
		pl->dir_x = 0.0;
		pl->dir_y = 1.0;
	}
	else if (c == 'E')
	{
		pl->dir_x = 1.0;
		pl->dir_y = 0.0;
	}
	else
	{
		pl->dir_x = -1.0;
		pl->dir_y = 0.0;
	}
}

// Set camera plane based on orientation char
static void	set_plane(t_player *pl, char c)
{
	if (c == 'N')
	{
		pl->plane_x = 0.66;
		pl->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		pl->plane_x = -0.66;
		pl->plane_y = 0.0;
	}
	else if (c == 'E')
	{
		pl->plane_x = 0.0;
		pl->plane_y = 0.66;
	}
	else
	{
		pl->plane_x = 0.0;
		pl->plane_y = -0.66;
	}
}

// Combine direction and plane setup
static void	set_orientation(t_player *pl, char c)
{
	set_dir(pl, c);
	set_plane(pl, c);
}

// Locate player start in map, set position and orientation
int	init_player(t_config *cfg)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width && !ft_strchr("NSEW", cfg->map[y][x]))
			x++;
		if (x < cfg->map_width)
			break ;
		y++;
	}
	if (y == cfg->map_height)
		return (-1);
	cfg->player.x = x + 0.5;
	cfg->player.y = y + 0.5;
	set_orientation(&cfg->player, cfg->map[y][x]);
	cfg->map[y][x] = '0';
	return (0);
}

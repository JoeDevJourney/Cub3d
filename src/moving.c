/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:42:23 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/15 16:04:28 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	moving_forward_backward(t_cub *cub)
{
	double	move_speed;

	move_speed = 0.05;
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_W))
	{
		if (cub->map[(int)(cub->pos_y)][(int)(cub->pos_x
				+ cub->dir_x * move_speed)] == 0)
			cub->pos_x += cub->dir_x * move_speed;
		if (cub->map[(int)(cub->pos_y
				+ cub->dir_y * move_speed)][(int)(cub->pos_x)] == 0)
			cub->pos_y += cub->dir_y * move_speed;
	}
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_S))
	{
		if (cub->map[(int)(cub->pos_y)][(int)(cub->pos_x
				- cub->dir_x * move_speed)] == 0)
			cub->pos_x -= cub->dir_x * move_speed;
		if (cub->map[(int)(cub->pos_y
				- cub->dir_y * move_speed)][(int)(cub->pos_x)] == 0)
			cub->pos_y -= cub->dir_y * move_speed;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:42:23 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/23 15:35:04 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	moving_left_right(t_cub	*cub)
{
	double	move_speed;

	move_speed = 0.05;
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_A))
	{
		if (cub->map[(int)(cub->pos_y)][(int)(cub->pos_x
				- cub->plane_x * move_speed)] == 0)
			cub->pos_x -= cub->plane_x * move_speed;
		if (cub->map[(int)(cub->pos_y
				- cub->plane_y * move_speed)][(int)(cub->pos_x)] == 0)
			cub->pos_y -= cub->plane_y * move_speed;
	}
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_D))
	{
		if (cub->map[(int)(cub->pos_y)][(int)(cub->pos_x
				+ cub->plane_x * move_speed)] == 0)
			cub->pos_x += cub->plane_x * move_speed;
		if (cub->map[(int)(cub->pos_y
				+ cub->plane_y * move_speed)][(int)(cub->pos_x)] == 0)
			cub->pos_y += cub->plane_y * move_speed;
	}
}

void	rotate_left_right(t_cub *cub)
{
	double	old_dir_x;
	double	rotspd;
	double	old_plane_x;

	rotspd = 0.05;
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_LEFT))
	{
		old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-rotspd) - cub->dir_y * sin(-rotspd);
		cub->dir_y = old_dir_x * sin(-rotspd) + cub->dir_y * cos(-rotspd);
		old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-rotspd)
			- cub->plane_y * sin(-rotspd);
		cub->plane_y = old_plane_x * sin(-rotspd) + cub->plane_y * cos(-rotspd);
	}
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_RIGHT))
	{
		old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(rotspd) - cub->dir_y * sin(rotspd);
		cub->dir_y = old_dir_x * sin(rotspd) + cub->dir_y * cos(rotspd);
		old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(rotspd) - cub->plane_y * sin(rotspd);
		cub->plane_y = old_plane_x * sin(rotspd) + cub->plane_y * cos(rotspd);
	}
}

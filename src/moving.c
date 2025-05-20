/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:42:23 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/20 13:32:08 by jbrandt          ###   ########.fr       */
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

// void	rotate_left_right(t_cub *cub)
// {
// 	double	old_dir_x;
// 	double	old_dir_y;
// 	double	rot_speed;

// 	rot_speed = 0.05;
// 	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_LEFT))
// 	{
// 		old_dir_x = cub->dir_x;
// 		cub->dir_x = cub->dir_x * cos(rot_speed);
// 	}
// }

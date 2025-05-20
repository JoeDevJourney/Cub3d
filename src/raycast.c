/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:23:09 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/09 15:25:50 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_ray_steps(t_ray *ray, t_cub *cub)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - cub->pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - cub->pos_y) * ray->delta_y;
	}
}

void	init_ray(t_ray *ray, t_cub *cub, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = cub->dir_x + cub->plane_x * ray->camera_x;
	ray->ray_dir_y = cub->dir_y + cub->plane_y * ray->camera_x;
	ray->map_x = (int)cub->pos_x;
	ray->map_y = (int)cub->pos_y;
	if (ray->ray_dir_x != 0)
		ray->delta_x = fabs(1.0 / ray->ray_dir_x);
	else
		ray->delta_x = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_y = fabs(1.0 / ray->ray_dir_y);
	else
		ray->delta_y = 1e30;
	set_ray_steps(ray, cub);
}

void	perform_dda(t_ray *ray, t_cub *cub)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
}

void	calculate_projection(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_y - ray->delta_y;
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

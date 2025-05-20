/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:29:42 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/15 16:11:18 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clear_buffer(t_cub *cub, uint32_t floor_color, uint32_t ceil_color)
{
	uint32_t	*pixels;
	int			y;
	int			x;

	pixels = (uint32_t *)cub->img->pixels;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				pixels[y * WIDTH + x] = ceil_color;
			else
				pixels[y * WIDTH + x] = floor_color;
			x++;
		}
		y++;
	}
}

void	render_column(t_cub *cub, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;
	uint32_t	*pixels;

	pixels = (uint32_t *)cub->img->pixels;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		if (ray->side == 1)
			color = 0xAAAAAAFF;
		else
			color = 0xFFFFFFFF;
		pixels[y * WIDTH + x] = color;
		y++;
	}
}

void	render_frame(t_cub *cub)
{
	int		x;
	t_ray	ray;

	clear_buffer(cub, cub->floor_color, cub->ceiling_color);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, cub, x);
		perform_dda(&ray, cub);
		calculate_projection(&ray);
		render_textured_column(cub, &ray, x);
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:22:40 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/09 16:54:12 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_cardinal_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	prepare_texture_data(t_tex *tex, t_ray *ray, t_cub *cub)
{
	double	wall_x;

	tex->dir = get_cardinal_direction(ray);
	if (ray->side == 0)
		wall_x = cub->pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = cub->pos_x + ray->perp_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex->tex_x = (int)(wall_x * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex->tex_x = TEXTURE_SIZE - tex->tex_x - 1;
	tex->step = 1.0 * TEXTURE_SIZE / ray->line_height;
	tex->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex->step;
}

void	draw_textured_column(t_cub *cub, t_ray *ray, t_tex *tex, int x)
{
	int			y;
	int			tex_y;
	uint32_t	color;
	uint32_t	*pixels;

	pixels = (uint32_t *)cub->img->pixels;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex->tex_pos & (TEXTURE_SIZE - 1);
		tex->tex_pos += tex->step;
		color = cub->textures[tex->dir][TEXTURE_SIZE * tex_y + tex->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		pixels[y * WIDTH + x] = color;
		y++;
	}
}

void	render_textured_column(t_cub *cub, t_ray *ray, int x)
{
	t_tex	tex;

	prepare_texture_data(&tex, ray, cub);
	draw_textured_column(cub, ray, &tex, x);
}

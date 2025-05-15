/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/15 16:05:02 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft/include/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1980
# define HEIGHT 1080
# define TEXTURE_SIZE 64

typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
}			t_dir;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	double			side_x;
	double			side_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_cub
{
	void			*mlx;
	mlx_t			*mlx_connect;
	mlx_image_t		*img;
	char			*img_addr;
	uint32_t		*textures[4]; //FOR NORTH EAST SOUTH WEST
	int				**map;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}			t_cub;

typedef struct s_tex
{
	int		dir;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_tex;

// Utils
void			malloc_error(void);
void			init_dummy_textures(t_cub *cub);
// Events
void			clean_exit(void *param);
void			create_image(t_cub *image);
void			handle_input(void *param);
// raycast
void			init_ray(t_ray *ray, t_cub *cub, int x);
void			perform_dda(t_ray *ray, t_cub *cub);
void			calculate_projection(t_ray *ray);
// render
void			render_textured_column(t_cub *cub, t_ray *ray, int x);
void			render_frame(t_cub *cub);
// moving
void			moving_forward_backward(t_cub *cub);
#endif
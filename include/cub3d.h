/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/23 15:19:46 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft/inc/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

//Colors used for terminal output____________________
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[38;5;214m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"
# define B_RED "\033[1;31m"// Bright Red
# define MAG "\033[0;35m"// Magenta
# define CYAN "\x1b[36m" //Cyan
// For screensize
# define WIDTH 1980
# define HEIGHT 1080
# define TEXTURE_SIZE 64

// Player Structure
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

// Color Structure
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Configuration Structure: textures, colors, maps
typedef struct s_config
{
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
}	t_config;

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
	mlx_texture_t	*textures[4];
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

// Parser Functions_________________________________________________
void			init_config(t_config *cfg);
int				parser(const char *path, t_config *cfg);
int				validate_cfg(t_config *cfg);
int				normalize_map(t_config *cfg);
int				init_player(t_config *cfg);
int				parse_color(t_config *cfg, char *line, int line_num);
int				parse_texture(t_config *cfg, const char *line, int line_num);

// Utils_____________________________________
char			*skip_spaces(char *s);
int				is_numeric(const char *s);
void			print_map(char **map);
int				report_err(int line, const char *msg);
void			free_config(t_config *cfg);
int				check_normalization(t_config *cfg);

// Utils3____________________________________
void			strip_nl(char *line);
int				check_extension(const char *path);
void			init_config(t_config *cfg);
int				is_element_line(char *line);
int				check_surroundings(t_config *cfg, int y, int x);

// Closure__________________________________
int				validate_map_closure_cells(t_config *cfg);

// Utils
void			malloc_error(void);
void			init_dummy_textures(t_cub *cub);
int				**convert_map_to_int(char **char_map, int height, int width);
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
void			load_textures(t_cub *cub, t_config *cfg);

// moving
void			moving_forward_backward(t_cub *cub);
void			moving_left_right(t_cub	*cub);
void			rotate_left_right(t_cub *cub);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/19 12:34:03 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../MLX42/include/MLX42/MLX42.h"
// # include "../libft/include/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

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
typedef struct	s_color
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


// Parser Functions
void	init_config(t_config *cfg);
int		parser(const char *path, t_config *cfg);
int		validate_cfg(t_config *cfg);
void	free_config(t_config *cfg);
int		normalize_map(t_config *cfg);
int		init_player(t_config *cfg);
int		report_err(int line, const char *msg);
int		parse_color(t_config *cfg, const char *line, int line_num);
int		is_numeric(const char *s);
int check_normalization(t_config *cfg);
void print_map(char **map);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/06 20:14:02 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../MLX42/include/MLX42/MLX42.h"
// # include "../libft/include/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>


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
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	t_color	floor;
	t_color	ceiling;
	char	**map;
	int		map_width;
	int		map_height;
}	t_config;


// Functions
int	parse_file(const char *path, t_config *cfg);
int	validate_cfg(t_config *cfg);

#endif
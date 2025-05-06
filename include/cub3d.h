/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/06 19:30:35 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1980
# define HEIGHT 1080

typedef struct s_cub
{
	void			*mlx;
	void			*window;
	mlx_t			*mlx_connect;
	mlx_image_t		*img;
	char			*img_buffer;
	char			*img_addr;
}			t_cub;

// Utils
void			malloc_error(void);
// Events
#endif
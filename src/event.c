/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:06:48 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/23 15:14:37 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_exit(void *param)
{
	t_cub	*image;

	image = (t_cub *)param;
	if (image->img)
		mlx_delete_image(image->mlx_connect, image->img);
	if (image->mlx_connect)
		mlx_terminate(image->mlx_connect);
	exit(0);
}

void	create_image(t_cub *image)
{
	image->img = mlx_new_image(image->mlx_connect, WIDTH, HEIGHT);
	if (!image->img->pixels)
	{
		mlx_terminate(image->mlx_connect);
		free(image->mlx_connect);
		malloc_error();
	}
	image->img_addr = (char *)image->img->pixels;
}

void	handle_input(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx_connect, MLX_KEY_ESCAPE))
		clean_exit(cub);
	render_frame(cub);
	moving_forward_backward(cub);
	moving_left_right(cub);
	rotate_left_right(cub);
}

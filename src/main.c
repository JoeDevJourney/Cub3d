/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:46:41 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/20 14:30:27 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_cub(t_cub *cub)
{
	int	map_data[10][10] = 
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,0,0,0,1},
		{1,0,0,0,1,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	int	i;
	cub->mlx_connect = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!cub->mlx_connect)
		exit(EXIT_FAILURE);
	create_image(cub);
	if (!cub->img || mlx_image_to_window(cub->mlx_connect, cub->img, 0, 0) < 0)
		exit(EXIT_FAILURE);
	cub->pos_x = 5.5;
	cub->pos_y = 5.5;
	cub->dir_x = -1.0;
	cub->dir_y = 0.0;
	cub->plane_x = 0.0;
	cub->plane_y = 0.66;
	cub->floor_color = 0x222222FF;
	cub->ceiling_color = 0x111111FF;
	i = 0;
	cub->map = malloc(sizeof(int *) * 10);
	if (!cub->map)
		exit(EXIT_FAILURE);
	while (i < 10)
	{
		cub->map[i] = malloc(sizeof(int) * 10);
		if (!cub->map[i])
			exit(EXIT_FAILURE);
		ft_memcpy(cub->map[i], map_data[i], sizeof(int) * 10);
		i++;
	}
	init_dummy_textures(cub);
}

int	main(void)
{
	t_cub	cub;

	printf("1: init_cub start\n");
	init_cub(&cub);
	printf("2: init_cub done\n");
	mlx_loop_hook(cub.mlx_connect, handle_input, &cub);
	printf("3: loop_hook set\n");
	mlx_loop(cub.mlx_connect);
	printf("4: loop running\n");
	mlx_terminate(cub.mlx_connect);
	return (0);
}

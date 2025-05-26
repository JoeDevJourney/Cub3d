/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/26 17:22:56 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "libft.h"
#include <unistd.h>

void	leaks(void)
{
	printf("\n");
	system("leaks cub3D");
}

// Produce a 32-bit word which, in little-endian memory, gives
// byte-0 = R, byte-1 = G, byte-2 = B, byte-3 = A.
// That matches MLX42’s RGBA ordering.

uint32_t	pack_rgba(t_color c)
{
	return (((c.r & 0xFFu) << 0)
		| ((c.g & 0xFFu) << 8)
		| ((c.b & 0xFFu) << 16)
		| (0xFFu << 24));
}

static void	init_cub(t_cub *cub, t_config *cfg)
{
	cub->mlx_connect = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!cub->mlx_connect)
	{
		free_config(cfg);
		exit(EXIT_FAILURE);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	create_image(cub);
	if (!cub->img || mlx_image_to_window(cub->mlx_connect, cub->img, 0, 0) < 0)
		exit(EXIT_FAILURE);
	cub->map = convert_map_to_int(cfg->map, cfg->map_height, cfg->map_width);
	cub->pos_x = cfg->player.x;
	cub->pos_y = cfg->player.y;
	cub->dir_x = cfg->player.dir_x;
	cub->dir_y = cfg->player.dir_y;
	cub->plane_x = cfg->player.plane_x;
	cub->plane_y = cfg->player.plane_y;
	cub->ceiling_color = pack_rgba(cfg->ceiling);
	cub->floor_color = pack_rgba(cfg->floor);
	load_textures(cub, cfg);
}

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_cub		cub;

	atexit(leaks);
	if (argc != 2)
	{
		ft_putendl_fd("Error: Usage -> ./cub3D <map_file.cub>", 2);
		return (1);
	}
	if (parser(argv[1], &cfg) < 0)
	{
		free_config(&cfg);
		ft_putendl_fd("Failed to load configuration.", 2);
		return (1);
	}
	print_map(cfg.map);
	init_cub(&cub, &cfg);
	mlx_loop_hook(cub.mlx_connect, handle_input, &cub);
	mlx_close_hook(cub.mlx_connect, clean_exit, &cub);
	mlx_loop(cub.mlx_connect);
	free_config(&cfg);
	return (0);
}

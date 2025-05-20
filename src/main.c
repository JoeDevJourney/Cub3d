/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/20 16:00:32 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

static void	init_cub(t_cub *cub, t_config *cfg)
{
	printf("init_cub: starting mlx_init\n");
	cub->mlx_connect = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!cub->mlx_connect)
	{
		printf("mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	printf("init_cub: mlx_init OK\n");

	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	create_image(cub);
	printf("init_cub: image created\n");

	if (!cub->img || mlx_image_to_window(cub->mlx_connect, cub->img, 0, 0) < 0)
	{
		printf("image to window failed\n");
		exit(EXIT_FAILURE);
	}
	printf("init_cub: image to window OK\n");

	cub->map = convert_char_map_to_int(cfg->map, cfg->map_height, cfg->map_width);
	printf("init_cub: map converted\n");
	cub->map = convert_char_map_to_int(cfg->map, cfg->map_height, cfg->map_width);
	cub->pos_x = cfg->player.x;
	cub->pos_y = cfg->player.y;
	cub->dir_x = cfg->player.dir_x;
	cub->dir_y = cfg->player.dir_y;
	cub->plane_x = cfg->player.plane_x;
	cub->plane_y = cfg->player.plane_y;
	cub->floor_color = (cfg->floor.r << 24) | (cfg->floor.g << 16) | (cfg->floor.b << 8) | 0xFF;
	cub->ceiling_color = (cfg->ceiling.r << 24) | (cfg->ceiling.g << 16) | (cfg->ceiling.b << 8) | 0xFF;

	init_dummy_textures(cub);
	printf("init_cub: dummy textures done\n");
}

int main(int argc, char **argv)
{
	t_config	cfg;
	t_cub		cub;

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
	// ----------------TO DEBUG -----------------------------
	printf("\n_______________TEXTURES_________________\n");
	printf("texture NO : %s\n", cfg.texture_no);
	printf("texture SO : %s\n", cfg.texture_so);
	printf("texture EA : %s\n", cfg.texture_ea);
	printf("texture WE : %s\n", cfg.texture_we);
	printf("\n_______________COLORS_________________\n");
	printf("color C; r:%d g:%d b:%d \n", cfg.ceiling.r, cfg.ceiling.g, cfg.ceiling.b);
	printf("color F; r:%d g:%d b:%d \n", cfg.floor.r, cfg.floor.g, cfg.floor.b);
	printf("\n_______________MAP DIMENSIONS_________________\n");	
	printf("map width : %d\n", cfg.map_width);
	printf("map height : %d\n", cfg.map_height);
	printf("\n_______________PLAYER_________________\n");		
	printf("player x : %f | player y : %f\n", cfg.player.x, cfg.player.y);
	printf("player xdir : %f | player ydir : %f\n", cfg.player.dir_x, cfg.player.dir_y);
	printf("plane x : %f | plane y : %f\n", cfg.player.plane_x, cfg.player.plane_y);
	
	printf("\n_______________MAP_________________\n");
	print_map(cfg.map); // PRINT NORMALIZED MAP
	
	// TO-DO: initialize MLX, load textures, start game loop
	printf("1: init_cub start\n");
	init_cub(&cub, &cfg);
	printf("2: init_cub done\n");
	mlx_loop_hook(cub.mlx_connect, handle_input, &cub);
	printf("3: loop_hook set\n");
	mlx_loop(cub.mlx_connect);
	printf("4: loop running\n");
	mlx_terminate(cub.mlx_connect);
	// cleanup of cfg.map and texture strings goes here
	
	free_config(&cfg);
	return (0);
}

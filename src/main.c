/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/20 14:01:13 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	t_config cfg;

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
	// cleanup of cfg.map and texture strings goes here
	
	free_config(&cfg);
	return (0);
}
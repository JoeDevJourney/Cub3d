/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 13:00:43 by jorgutie         ###   ########.fr       */
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
		ft_putendl_fd("Usage: ./cub3D <map_file.cub>", 2);
		return (1);
	}
	if (parser(argv[1], &cfg) < 0)
	{
		free_config(&cfg);
		ft_putendl_fd("Failed to load configuration.", 2);
		return (1);
	}

	// ----------------TO DEBUG -----------------------------
	printf("color : %d\n", cfg.floor.b);
	printf("texture no : %s\n", cfg.texture_no);
	printf("map width : %d\n", cfg.map_width);
	printf("map height : %d\n", cfg.map_height);
	printf("player x : %f, y : %f\n", cfg.player.x, cfg.player.y);
	printf("player xdir : %f, ydir : %f\n", cfg.player.dir_x, cfg.player.dir_y);
	
	 
	print_map(cfg.map); // PRINT NORMALIZED MAP
	
	// TO-DO: initialize MLX, load textures, start game loop
	// cleanup of cfg.map and texture strings goes here
	free_config(&cfg);
	return (0);
}
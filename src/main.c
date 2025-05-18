/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/18 14:49:12 by jorgutie         ###   ########.fr       */
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

	printf("color : %d\n", cfg.floor.b);
	printf("texture no : %s\n", cfg.texture_no);
	printf("map width : %d\n", cfg.map_width);
	printf("map height : %d\n", cfg.map_height);

	// TO-DO: initialize MLX, load textures, start game loop
	// cleanup of cfg.map and texture strings goes here
	free_config(&cfg);
	return (0);
}
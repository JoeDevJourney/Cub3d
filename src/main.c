/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/12 13:00:25 by jorgutie         ###   ########.fr       */
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
		ft_putendl_fd("Failed to load configuration.", 2);
		return (1);
	}
	// TO-DO: initialize MLX, load textures, start game loop
	// cleanup of cfg.map and texture strings goes here

	return (0);
}
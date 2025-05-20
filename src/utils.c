/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:48 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/20 15:54:33 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	malloc_error(void)
{
	perror("Malloc Error: ");
	exit(EXIT_FAILURE);
}

void	init_dummy_textures(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		cub->textures[i] = malloc(sizeof(uint32_t) * TEXTURE_SIZE
				* TEXTURE_SIZE);
		if (!cub->textures[i])
			exit(EXIT_FAILURE);
		j = 0;
		while (j < TEXTURE_SIZE * TEXTURE_SIZE)
		{
			if (i == 0)
				cub->textures[i][j] = 0xFF0000FF;
			else if (i == 1)
				cub->textures[i][j] = 0x00FF00FF;
			else if (i == 2)
				cub->textures[i][j] = 0x0000FFFF;
			else
				cub->textures[i][j] = 0xFFFF00FF;
			j++;
		}
		i++;
	}
}

int	**convert_char_map_to_int(char **char_map, int height, int width)
{
	int	**int_map = malloc(sizeof(int *) * height);
	int	i, j;

	for (i = 0; i < height; i++)
	{
		int_map[i] = malloc(sizeof(int) * width);
		for (j = 0; j < width; j++)
		{
			if (char_map[i][j] == ' ' || char_map[i][j] == '\0')
				int_map[i][j] = 1; // treat empty space as wall
			else if (char_map[i][j] == '1')
				int_map[i][j] = 1;
			else
				int_map[i][j] = 0;
		}
	}
	return int_map;
}

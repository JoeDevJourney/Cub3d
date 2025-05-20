/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:48 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/20 16:34:53 by jbrandt          ###   ########.fr       */
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

static int	*convert_map_row(char *line, int width)
{
	int	*row;
	int	j;

	row = malloc(sizeof(int) * width);
	if (!row)
		return (NULL);
	j = 0;
	while (j < width)
	{
		if (line[j] == ' ' || line[j] == '\0')
			row[j] = 1;
		else if (line[j] == '1')
			row[j] = 1;
		else
			row[j] = 0;
		j++;
	}
	return (row);
}

int	**convert_map_to_int(char **char_map, int height, int width)
{
	int	**int_map;
	int	i;

	int_map = malloc(sizeof(int *) * height);
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		int_map[i] = convert_map_row(char_map[i], width);
		if (!int_map[i])
			return (NULL);
		i++;
	}
	return (int_map);
}

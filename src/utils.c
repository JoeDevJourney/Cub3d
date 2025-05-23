/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:48 by jbrandt           #+#    #+#             */
/*   Updated: 2025/05/23 14:59:03 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	malloc_error(void)
{
	perror("Malloc Error: ");
	exit(EXIT_FAILURE);
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

// load_textures:
// For each of the four cardinal texture paths in cfg, load the
// PNG into an mlx_texture_t, error out on failure.
void	load_textures(t_cub *cub, t_config *cfg)
{
	cub->textures[NORTH] = mlx_load_png(cfg->texture_no);
	if (!cub->textures[NORTH])
	{
		perror("mlx_load_png NO");
		exit(EXIT_FAILURE);
	}
	cub->textures[SOUTH] = mlx_load_png(cfg->texture_so);
	if (!cub->textures[SOUTH])
	{
		perror("mlx_load_png SO");
		exit(EXIT_FAILURE);
	}
	cub->textures[WEST] = mlx_load_png(cfg->texture_we);
	if (!cub->textures[WEST])
	{
		perror("mlx_load_png WE");
		exit(EXIT_FAILURE);
	}
	cub->textures[EAST] = mlx_load_png(cfg->texture_ea);
	if (!cub->textures[EAST])
	{
		perror("mlx_load_png EA");
		exit(EXIT_FAILURE);
	}
}

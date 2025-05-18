/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:12:46 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/18 18:01:39 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Compute height and width of the map
static void	compute_dimensions(char **map, int *h, int *w)
{
	int	len;

	*h = 0;
	*w = 0;
	while (map[*h])
	{
		len = ft_strlen(map[*h]);
		if (len > *w)
			*w = len;
		(*h)++;
	}
}

// Copy src into dst, padding with spaces
static int	pad_row(const char *src, char *dst, int width)
{
	int	i;
	int	len;

	len = ft_strlen(src);
	i = 0;
	while (i < width)
	{
		if (i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (0);
}

// Build a new padded map
static int	build_map(char **old_map,
	char ***out_map, int h, int w)
{
	char	**nm;
	int		i;

	nm = malloc(sizeof(char *) * (h + 1));
	if (nm == NULL)
		return (ft_putendl_fd("Error: memory allocation failed", 2), -1);
	i = 0;
	while (i < h)
	{
		nm[i] = malloc(w + 1);
		if (nm[i] == NULL)
		{
			while (i-- > 0)
				free(nm[i]);
			free(nm);
			ft_putendl_fd("Error: memory allocation failed", 2);
			return (-1);
		}
		pad_row(old_map[i], nm[i], w);
		i++;
	}
	nm[h] = NULL;
	*out_map = nm;
	return (0);
}

// Free an array of strings
static void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// Normalize the map: allocate padded map and free old
int	normalize_map(t_config *cfg)
{
	int		h;
	int		w;
	char	**nm;

	compute_dimensions(cfg->map, &h, &w);
	if (build_map(cfg->map, &nm, h, w) < 0)
		return (-1);
	free_map(cfg->map);
	cfg->map = nm;
	cfg->map_height = h;
	cfg->map_width = w;
	printf("map width : %d\n", cfg->map_width);
	printf("map height : %d\n", cfg->map_height);
	return (0);
}

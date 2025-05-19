/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:38:21 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 20:16:46 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// /* Debug closure failures: prints y,x,c */
// static int debug_check_surroundings(t_config *cfg, int y, int x)
// {
// 	char c;

// 	c = cfg->map[y][x];
// 	if (!check_surroundings(cfg, y, x))
// 	{
// 		ft_putstr_fd("Closure fail at (", 2);
// 		ft_putnbr_fd(y, 2);
// 		ft_putstr_fd(",", 2);
// 		ft_putnbr_fd(x, 2);
// 		ft_putstr_fd(") char='", 2);
// 		ft_putchar_fd(c, 2);
// 		ft_putendl_fd("'", 2);
// 		return (0);
// 	}
// 	return (1);
// }

// Count player start positions in map
static int	count_player(char **map)
{
	int	y;
	int	x;
	int	cnt;

	y = 0;
	cnt = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

// // Check that cell at (y,x) is enclosed by walls or valid chars
// static int check_surroundings(char **map, int y, int x)
// {
// 	int rows = 0;
// 	int len;

// 	/* count total rows */
// 	while (map[rows])
// 		rows++;
// 	/* above */
// 	if (y <= 0)
// 		return (0);
// 	len = ft_strlen(map[y - 1]);
// 	if (x >= len || map[y - 1][x] == ' ')
// 		return (0);

// 	/* below */
// 	if (y >= rows - 1)
// 		return (0);
// 	len = ft_strlen(map[y + 1]);
// 	if (x >= len || map[y + 1][x] == ' ')
// 		return (0);

// 	/* left */
// 	if (x <= 0 || map[y][x - 1] == ' ')
// 		return (0);

// 	/* right */
// 	len = ft_strlen(map[y]);
// 	if (x >= len - 1 || map[y][x + 1] == ' ')
// 		return (0);

// 	return (1);
// }

// Validate textures and colors presence */
static int	validate_textures_colors(t_config *cfg)
{
	if (!cfg->texture_no || !cfg->texture_so
		|| !cfg->texture_we || !cfg->texture_ea)
	{
		ft_putendl_fd("Error: missing texture", 2);
		return (-1);
	}
	if (cfg->floor.r < 0 || cfg->floor.g < 0 || cfg->floor.b < 0
		|| cfg->ceiling.r < 0 || cfg->ceiling.g < 0 || cfg->ceiling.b < 0)
	{
		ft_putendl_fd("Error: missing color", 2);
		return (-1);
	}
	return (0);
}

// Validate exactly one player start
static int	validate_player(char **map)
{
	if (count_player(map) != 1)
	{
		ft_putendl_fd("Error: invalid player start", 2);
		return (-1);
	}
	return (0);
}

// // Validate map closure: every walkable cell enclosed
// static int validate_map_closure(char **map)
// {
// 	int y;
// 	int x;

// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (ft_strchr("0NSEW", map[y][x])
// 			 && !check_surroundings(map, y, x))
// 			{
// 				ft_putendl_fd("Error: map not closed", 2);
// 				return (-1);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

// Validate each cell: allowed chars and closure
static int	validate_map_structure(t_config *cfg)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			c = cfg->map[y][x];
			if (!(c == '1' || c == ' ' || c == '0'
					|| ft_strchr("NSEW", c)))
				return (ft_putendl_fd("Error: invalid map char", 2), -1);
			if ((c == '0' || ft_strchr("NSEW", c))
				&& !check_surroundings(cfg, y, x))
				return (ft_putendl_fd("Error: map not closed", 2), -1);
			//  && !check_surroundings(cfg, y, x))
			// 	return (ft_putendl_fd("Error: map not closed", 2), -1);
			x++;
		}
		y++;
	}
	return (0);
}

// Validate entire configuration
int	validate_cfg(t_config *cfg)
{
	char	**m;

	m = cfg->map;
	if (validate_textures_colors(cfg) < 0)
		return (-1);
	if (!m)
		return (ft_putendl_fd("Error: empty map", 2), -1);
	if (validate_player(m) < 0)
		return (-1);
	if (validate_map_structure(cfg) < 0)
		return (-1);
	return (0);
}

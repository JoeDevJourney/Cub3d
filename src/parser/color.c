/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:49:19 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 15:37:55 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check ID is F/C and next is space 
static int	check_color_id(const char *p, int line_num)
{
	if (*p != 'F' && *p != 'C')
		return (report_err(line_num, "invalid color ID"));
	if (*(p + 1) != ' ')
		return (report_err(line_num, "missing space after color ID"));
	return (1);
}

//Split into exactly 3 comma-separated tokens
static char	**get_color_parts(const char *str, int line_num)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_free_2d(parts);
		report_err(line_num, "color must have 3 values");
		return (NULL);
	}
	return (parts);
}

// Trim token, ensure numeric, atoi, and free
static int	get_color_comp(const char *tok, int *out, int line_num)
{
	char	*trim;

	trim = ft_strtrim(tok, " 	");
	if (!trim)
		return (report_err(line_num, "memory allocation failed"));
	if (!is_numeric(trim))
	{
		free(trim);
		return (report_err(line_num, "non-numeric color value"));
	}
	*out = ft_atoi(trim);
	free(trim);
	return (0);
}

// Assign to floor or ceiling
static int	assign_color(t_config *cfg, char id, t_color col, int line_num)
{
	if (id == 'F' && cfg->floor.r < 0)
		cfg->floor = col;
	else if (id == 'C' && cfg->ceiling.r < 0)
		cfg->ceiling = col;
	else
		return (report_err(line_num, "duplicate color ID"));
	return (0);
}

// Parse “F R,G,B” or “C R,G,B”, allowing leading spaces
int	parse_color(t_config *cfg, char *line, int line_num)
{
	const char	*p;
	char		**parts;
	t_color		col;

	p = skip_spaces(line);
	if (!check_color_id(p, line_num))
		return (-1);
	parts = get_color_parts(p + 2, line_num);
	if (!parts)
		return (-1);
	if (get_color_comp(parts[0], &col.r, line_num) < 0
		|| get_color_comp(parts[1], &col.g, line_num) < 0
		|| get_color_comp(parts[2], &col.b, line_num) < 0)
	{
		ft_free_2d(parts);
		return (-1);
	}
	ft_free_2d(parts);
	if (col.r < 0 || col.r > 255
		|| col.g < 0 || col.g > 255
		|| col.b < 0 || col.b > 255)
		return (report_err(line_num, "color value out of range"));
	return (assign_color(cfg, *p, col, line_num));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:03:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/21 20:37:49 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Assign the duplicated path to the correct texture slot
static int	assign_texture(t_config *cfg, const char *id,
	char *path, int line_num)
{
	if (!ft_strcmp(id, "NO") && !cfg->texture_no)
		cfg->texture_no = path;
	else if (!ft_strcmp(id, "SO") && !cfg->texture_so)
		cfg->texture_so = path;
	else if (!ft_strcmp(id, "WE") && !cfg->texture_we)
		cfg->texture_we = path;
	else if (!ft_strcmp(id, "EA") && !cfg->texture_ea)
		cfg->texture_ea = path;
	else
	{
		free(path);
		report_err(line_num, "unknown or duplicate texture ID");
		return (-1);
	}
	return (0);
}

// Split, validate count, duplicate path
static char	*extract_texture_path(const char *line, int line_num)
{
	char	**parts;
	int		count;
	char	*dup;

	parts = ft_split(line, ' ');
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
	{
		ft_free_2d(parts);
		report_err(line_num, "invalid texture format");
		return (NULL);
	}
	dup = ft_strdup(parts[1]);
	if (!dup)
	{
		ft_free_2d(parts);
		report_err(line_num, "memory allocation failed");
		return (NULL);
	}
	ft_free_2d(parts);
	return (dup);
}

int	parse_texture(t_config *cfg, const char *line, int line_num)
{
	char	*path;
	char	**parts;
	char	*id;
	int		res;

	path = extract_texture_path(line, line_num);
	if (!path)
		return (-1);
	parts = ft_split(line, ' ');
	id = parts[0];
	res = assign_texture(cfg, id, path, line_num);
	ft_free_2d(parts);
	return (res);
}

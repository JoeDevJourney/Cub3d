/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:48 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 15:17:31 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Skip leading spaces
char *skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

// Check if string is numeric
int	is_numeric(const char *s)
{
	if (s == NULL)
		return (0);
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (ft_isdigit(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

// Print every row of the normalized map to stdout
void print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		ft_putendl_fd(map[i], 1);
		i++;
	}
}
// helper to print and return error
int	report_err(int line, const char *msg)
{
	ft_putstr_fd("Error (line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("): ", 2);
	ft_putendl_fd((char *)msg, 2);
	return (-1);
}

//Free all cfg allocations (textures + map)
void	free_config(t_config *cfg)
{
	int	i;

	if (cfg->texture_no)
		free(cfg->texture_no);
	if (cfg->texture_so)
		free(cfg->texture_so);
	if (cfg->texture_we)
		free(cfg->texture_we);
	if (cfg->texture_ea)
		free(cfg->texture_ea);
	if (cfg->map)
	{
		i = 0;
		while (cfg->map[i])
			free(cfg->map[i++]);
		free(cfg->map);
	}
}

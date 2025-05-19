/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:48 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 13:56:44 by jorgutie         ###   ########.fr       */
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

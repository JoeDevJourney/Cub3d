/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:30:40 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/19 13:32:30 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Helper function to report row length mismatch
static int report_row_error(int row, int actual, int expected)
{
	ft_putstr_fd("Normalization error on row ", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(": got ", 2);
	ft_putnbr_fd(actual, 2);
	ft_putstr_fd(" expected ", 2);
	ft_putnbr_fd(expected, 2);
	ft_putendl_fd("", 2);
	return (-1);
}

// Helper function to report row count mismatch
static int report_count_error(int actual, int expected)
{
	ft_putstr_fd("Normalization error: row count ", 2);
	ft_putnbr_fd(actual, 2);
	ft_putstr_fd(" expected ", 2);
	ft_putnbr_fd(expected, 2);
	ft_putendl_fd("", 2);
	return (-1);
}

// Verify that all rows have correct width
static int check_row_widths(t_config *cfg)
{
	int i;
	int len;

	i = 0;
	while (cfg->map[i])
	{
		len = ft_strlen(cfg->map[i]);
		if (len != cfg->map_width)
			return report_row_error(i, len, cfg->map_width);
		i++;
	}
	return i;
}

// Verify that normalization produced a true rectangle
int check_normalization(t_config *cfg)
{
	int row_count;

	row_count = check_row_widths(cfg);
	if (row_count == -1)
		return (-1);
	if (row_count != cfg->map_height)
		return report_count_error(row_count, cfg->map_height);
	return (0);
}

// // Verify that normalization produced a true rectangle
// int check_normalization(t_config *cfg)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	while (cfg->map[i])
// 	{
// 		len = ft_strlen(cfg->map[i]);
// 		if (len != cfg->map_width)
// 		{
// 			ft_putstr_fd("Normalization error on row ", 2);
// 			ft_putnbr_fd(i, 2);
// 			ft_putstr_fd(": got ", 2);
// 			ft_putnbr_fd(len, 2);
// 			ft_putstr_fd(" expected ", 2);
// 			ft_putnbr_fd(cfg->map_width, 2);
// 			ft_putendl_fd("", 2);
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	if (i != cfg->map_height)
// 	{
// 		ft_putstr_fd("Normalization error: row count ", 2);
// 		ft_putnbr_fd(i, 2);
// 		ft_putstr_fd(" expected ", 2);
// 		ft_putnbr_fd(cfg->map_height, 2);
// 		ft_putendl_fd("", 2);
// 		return (-1);
// 	}
// 	return (0);
// }
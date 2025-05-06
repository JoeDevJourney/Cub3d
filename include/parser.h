/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:00:10 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/06 18:17:55 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

//Colors used for terminal output____________________
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[38;5;214m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"
# define B_RED "\033[1;31m"// Bright Red
# define MAG "\033[0;35m"// Magenta
# define CYAN "\x1b[36m" //Cyan

// Map Struct______________________________
typedef struct s_strc_map
{
	char			*value;
	struct s_token	*next;
}	t_strc_map;

#endif
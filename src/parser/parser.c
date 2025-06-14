/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:57:32 by jorgutie          #+#    #+#             */
/*   Updated: 2025/05/26 14:29:59 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Add a map line to cfg->map array, return 0 on success
static int	add_map_line(t_config *cfg, const char *line)
{
	char	**new_map;
	int		count;
	int		i;

	count = 0;
	while (cfg->map && cfg->map[count])
		count++;
	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (-1);
	i = 0;
	while (i < count)
	{
		new_map[i] = cfg->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	i++;
	new_map[i] = NULL;
	free(cfg->map);
	cfg->map = new_map;
	return (0);
}

// Process a single non-empty line
static int	process_line(t_config *cfg, char *line, int line_num)
{
	if (is_element_line(line) == 1)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			return (parse_texture(cfg, line, line_num));
		return (parse_color(cfg, line, line_num));
	}
	return (add_map_line(cfg, line));
}

// // Process a single config line: skip blanks. 
// 1) skip blank lines, 2) if we haven't started the map yet, 
// look only for element lines. 3) otherwise, it's a mapline 
// it preserves all spaces
static int	process_config_line(t_config *cfg, char *line,
	int *map_started, int line_num)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0')
		return (1);
	if (!*map_started && is_element_line(trimmed))
		return (process_line(cfg, trimmed, line_num));
	*map_started = 1;
	return (add_map_line(cfg, line));
}

// Read all lines, dispatch element vs map, report errors
int	parse_file(int fd, t_config *cfg)
{
	int		map_started;
	int		line_num;
	char	*line;
	int		status;

	map_started = 0;
	line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_nl(line);
		line_num++;
		status = process_config_line(cfg, line, &map_started, line_num);
		if (status < 0)
			return (free(line), -1);
		if (status > 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

// Initialization of CFG. Check extension ".cub". Open the file
// To read the .cub file and add the info for the config structure
int	parser(const char *path, t_config *cfg)
{
	int	fd;
	int	ret;

	init_config(cfg);
	if (!check_extension(path))
		return (report_err(0, "file must end in .cub"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error: openning file .cub"), -1);
	ret = parse_file(fd, cfg);
	close(fd);
	if (ret < 0)
		return (-1);
	if (!cfg->map || !cfg->map[0])
		return (report_err(0, "empty or invalid .cub file"));
	if (normalize_map(cfg) < 0 || check_normalization(cfg) < 0
		|| validate_cfg(cfg) < 0)
		return (-1);
	if (validate_cfg(cfg) < 0)
		return (-1);
	if (init_player(cfg) < 0)
		return (report_err(0, "invalid or missing player start"));
	return (0);
}

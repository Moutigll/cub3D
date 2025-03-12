/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:56:15 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/12 15:15:03 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid_map_char(t_main *data, int x, int y, int *player_count)
{
	char	c;

	c = data->map[y][x];
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		return (printf("Error: Invalid character in map\n"), 0);
	if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
		|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
	{
		if (*player_count)
			return (printf("Error: Multiple players found\n"), 0);
		init_player(data->player, x, y, data->map[y][x]);
		data->map[y][x] = '0';
		(*player_count)++;
	}
	return (1);
}

static int	check_line_length(t_main *data, int y, size_t max_len)
{
	char	*tmp;

	if (ft_strlen(data->map[y]) < max_len)
	{
		tmp = malloc(max_len + 1);
		if (!tmp)
			return (printf("Error: Map allocation failed\n"), 0);
		ft_memset(tmp, ' ', max_len);
		ft_memcpy(tmp, data->map[y], ft_strlen(data->map[y]));
		tmp[max_len] = '\0';
		free(data->map[y]);
		data->map[y] = tmp;
	}
	return (1);
}

static int	check_map_validity(t_main *data)
{
	int		x;
	int		y;
	int		player_count;
	size_t	max_len;

	player_count = 0;
	y = 0;
	max_len = get_max_line_length(data->map);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!is_valid_map_char(data, x, y, &player_count))
				return (0);
			x++;
		}
		if (!check_line_length(data, y, max_len))
			return (0);
		y++;
	}
	if (player_count == 0)
		return (printf("Error: No player found in map\n"), 0);
	return (1);
}

static int	read_and_parse_map(t_main *data, int fd, char *last_line)
{
	char	*line;
	char	*map_str;
	char	*tmp;

	map_str = last_line;
	if (!map_str)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		if (!tmp)
			return (-1);
		map_str = tmp;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->map = ft_split(map_str, '\n');
	free(map_str);
	if (!data->map)
		return (printf("Error: Map allocation failed\n"), -1);
	return (0);
}

int	parse_map(t_main *data, const char *file_path)
{
	int		fd;
	char	*line;
	char	**map_cp;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Failed to open map file\n"), -1);
	line = parse_metadata(fd, data);
	if (read_and_parse_map(data, fd, line) == -1)
		return (-1);
	if (!check_map_validity(data))
		return (free_data(data), -1);
	map_cp = cpy_map(data->map);
	flood_fill(data, map_cp, (int)data->player->player_x,
		(int)data->player->player_y);
	if (!map_is_flooded(map_cp))
		return (printf("Error: The map is not closed\n"),
			free_data(data), -1);
	free_tab((void **)map_cp);
	return (0);
}

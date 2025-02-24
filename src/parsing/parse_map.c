/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:56:15 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/24 15:45:49 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_valid_metadata(char *line)
{
	const char	*metadata[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	int			i;

	i = 0;
	while (i < 6)
	{
		if ((line[0] == '\n' && line[1] == '\0') || line[0] == '\0')
			return (1);
		if (!ft_strncmp(line, metadata[i], ft_strlen(metadata[i])))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_color(char *line)
{
	char	**rgb;
	int		i;
	int		value;

	rgb = ft_split(line, ',');
	if (!rgb || ft_tablen((void **)rgb) != 3)
	{
		free_tab((void **)rgb);
		printf("Error: Invalid color format for: %s\n", line);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
		{
			printf("Error: Invalid color value for: %s\n", line);
			free_tab((void **)rgb);
			return (0);
		}
		i++;
	}
	free_tab((void **)rgb);
	return (1);
}

int	parse_color(char *line)
{
	int		nb_commas;
	int		r;
	int		g;
	int		b;
	char	**rgb;
	int		i;

	nb_commas = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			nb_commas++;
		i++;
	}
	if (nb_commas != 2)
	{
		printf("Error: Invalid color format for: %s\n", line);
		return (-1);
	}
	if (!is_valid_color(line))
		return (-1);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_tab((void **)rgb);
	return (r << 16 | g << 8 | b);
}

char	*parse_metadata(int fd, t_main *data)
{
	char	*line;
	char	*map_str;
	int		metadata_count;

	metadata_count = 0;
	line = get_next_line(fd);
	while (line && metadata_count < 6 && is_valid_metadata(line))
	{
		if (!ft_strncmp(line, "NO ", 3))
			data->textures->north_path = ft_strcut(line + 3, '\n');
		else if (!ft_strncmp(line, "SO ", 3))
			data->textures->south_path = ft_strcut(line + 3, '\n');
		else if (!ft_strncmp(line, "WE ", 3))
			data->textures->west_path = ft_strcut(line + 3, '\n');
		else if (!ft_strncmp(line, "EA ", 3))
			data->textures->east_path = ft_strcut(line + 3, '\n');
		else if (!ft_strncmp(line, "F ", 2))
			data->textures->floor_color = parse_color(line + 2);
		else if (!ft_strncmp(line, "C ", 2))
			data->textures->ceiling_color = parse_color(line + 2);
		else
			metadata_count--;
		metadata_count++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		map_str = ft_strdup(line);
	free(line);
	if (metadata_count != 6)
		return (printf("Error: Wrong metadata number, found %d\n", metadata_count), NULL);
	return (map_str);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	check_map_validity(t_main *data)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!is_valid_map_char(data->map[y][x]))
				return (printf("Error: Invalid character in map [%c]\n", data->map[y][x]), 0);
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (printf("Error: Multiple players found\n"), 0);
				init_player(data->player, x, y, data->map[y][x]);
				data->map[y][x] = '0';
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (printf("Error: No player found in map\n"), 0);
	return (1);
}

int	get_max_line_length(char **map)
{
	int	max_len;
	int	len;
	int	i;

	max_len = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

int	read_and_parse_map(t_main *data, int fd, char *last_line)
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

int	adjust_map_line_lengths(t_main *data)
{
	int		max_line_len;
	int		i;
	int		len;
	char	*tmp;

	max_line_len = get_max_line_length(data->map);
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len < max_line_len)
		{
			tmp = malloc(max_line_len + 1);
			if (!tmp)
				return (-1);
			ft_memset(tmp, ' ', max_line_len);
			tmp[max_line_len] = '\0';
			ft_memcpy(tmp, data->map[i], len);
			free(data->map[i]);
			data->map[i] = tmp;
		}
		i++;
	}
	if (!check_map_validity(data))
		return (-1);
	return (0);
}

int	parse_map(t_main *data, const char *file_path)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Failed to open map file\n"), -1);
	line = parse_metadata(fd, data);
	if (read_and_parse_map(data, fd, line) == -1)
		return (-1);
	if (adjust_map_line_lengths(data) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:28:23 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/12 16:41:21 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid_metadata(char *line)
{
	const char	*metadata[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	int			i;

	if (!line || line[0] == '\n' || line[0] == '\0')
		return (1);
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(line, metadata[i], ft_strlen(metadata[i])))
			return (1);
		i++;
	}
	return (0);
}

static int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb || ft_tablen((void **)rgb) != 3)
	{
		printf("Error: Invalid color format for: %s", line);
		free_tab((void **)rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error: Invalid color value for: %s", line);
		free_tab((void **)rgb);
		return (-1);
	}
	free_tab((void **)rgb);
	return (r << 16 | g << 8 | b);
}

static int	extract_metadata(char *line, t_main *data)
{
	if (!ft_strncmp(line, "NO ", 3))
		data->textures->north_path = ft_rm_blanks(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		data->textures->south_path = ft_rm_blanks(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		data->textures->west_path = ft_rm_blanks(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		data->textures->east_path = ft_rm_blanks(line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		data->textures->floor_color = parse_color(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		data->textures->ceiling_color = parse_color(line + 2);
	else
		return (0);
	return (1);
}

char	*parse_metadata(int fd, t_main *data)
{
	char	*line;
	int		metadata_count;

	metadata_count = 0;
	line = get_next_line(fd);
	while (line && metadata_count < 6 && is_valid_metadata(line))
	{
		metadata_count += extract_metadata(line, data);
		free(line);
		line = get_next_line(fd);
	}
	if (metadata_count != 6)
		return (printf("Error: Wrong metadata number,\
 found %d\n", metadata_count), NULL);
	if (data->textures->floor_color == -1
		|| data->textures->ceiling_color == -1)
		return (NULL);
	return (line);
}

/*For check map validity*/
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

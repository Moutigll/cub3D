/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:56:15 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 21:52:30 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*Temporary function that just get the content from a file
and put it in a char **
It's only for testing with a known to be valid map file
*/

void	parse_map(t_main *data, const char *file_path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = ft_getnline((char *)file_path);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur lors de l'ouverture du fichier %s\n", file_path);
		exit(1);
	}
	data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
	{
		printf("Erreur d'allocation de mémoire pour la carte\n");
		exit(1);
	}
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map[line_count] = ft_strdup(line);
		if (!data->map[line_count])
		{
			printf("Erreur d'allocation de mémoire pour la ligne %d de la carte\n", line_count);
			exit(1);
		}
		line_count++;
		free(line);
	}
	data->map[line_count] = NULL;
	close(fd);
}
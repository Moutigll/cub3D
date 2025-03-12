/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:03:02 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/12 16:43:41 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static t_mlx_img	*open_img(t_main *data, char *path)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(data->mlx,
			path, &img->width, &img->height);
	if (!img->img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian);
	return (img);
}

int	init_textures(t_main *data)
{
	data->textures->north = open_img(data, data->textures->north_path);
	if (!data->textures->north)
		return (printf("Error: Failed to open north texture\n"), 0);
	data->textures->south = open_img(data, data->textures->south_path);
	if (!data->textures->south)
		return (printf("Error: Failed to open south texture\n"), 0);
	data->textures->west = open_img(data, data->textures->west_path);
	if (!data->textures->west)
		return (printf("Error: Failed to open west texture\n"), 0);
	data->textures->east = open_img(data, data->textures->east_path);
	if (!data->textures->east)
		return (printf("Error: Failed to open east texture\n"), 0);
	data->textures->middle = HEIGHT / 2;
	data->textures->north->bpp /= 8;
	data->textures->south->bpp /= 8;
	data->textures->west->bpp /= 8;
	data->textures->east->bpp /= 8;
	return (1);
}

t_mlx_font	*init_font(t_main *data)
{
	t_mlx_font	*font;

	font = malloc(sizeof(t_mlx_font));
	if (!font)
		return (NULL);
	font->path = ft_strdup("assets/font.dim");
	if (!font->path)
		return (free(font), NULL);
	font->font = open_img(data, "assets/font.xpm");
	font->letters_str = NULL;
	font->letters = NULL;
	font->mlx = data->mlx;
	return (font);
}

static void	set_player_direction(t_player *player, char dir, double fov_rad)
{
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->cam_plane_x = fov_rad;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->cam_plane_x = -fov_rad;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->cam_plane_y = fov_rad;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->cam_plane_y = -fov_rad;
	}
}

void	init_player(t_player *player, int x, int y, char dir)
{
	double	fov_rad;

	player->player_x = x + 0.5;
	player->player_y = y + 0.5;
	player->dir_x = 0;
	player->dir_y = 0;
	player->cam_plane_x = 0;
	player->cam_plane_y = 0;
	player->fov = FOV;
	fov_rad = tan((player->fov * PI / 180.0) / 2.0);
	set_player_direction(player, dir, fov_rad);
}

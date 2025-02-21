/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:34:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 09:22:59 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_mlx_font	*init_font(t_main *data)
{
	t_mlx_font	*font;

	font = malloc(sizeof(t_mlx_font));
	if (!font)
		return (NULL);
	font->font = malloc(sizeof(t_mlx_img));
	if (!font->font)
		return (free(font), NULL);
	font->path = ft_strdup("assets/font.dim");
	if (!font->path)
		return (free(font->font), free(font), NULL);
	font->font->img = mlx_xpm_file_to_image(data->mlx, "assets/font.xpm",
			&font->font->width, &font->font->height);
	font->font->addr = mlx_get_data_addr(font->font->img,
			&font->font->bpp, &font->font->size_line, &font->font->endian);
	font->letters_str = NULL;
	font->letters = NULL;
	return (font);
}

t_key_state	*init_key_state(void)
{
	t_key_state	*key_state;

	key_state = malloc(sizeof(t_key_state));
	if (!key_state)
		return (NULL);
	key_state->left = False;
	key_state->right = False;
	key_state->up = False;
	key_state->down = False;
	return (key_state);
}

void	set_player_direction(t_player *player, char dir, double fov_rad)
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

t_mlx_img	*allocate_img(void *mlx)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_mlx_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img->img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(
			img->img, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

t_main	*init_main(void)
{
	t_main	*data;

	data = malloc(sizeof(t_main));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free(data), NULL);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
		return (free(data), NULL);
	data->img = allocate_img(data->mlx);
	if (!data->img)
		return (free(data), NULL);
	data->font = init_font(data);
	if (!data->font || !mlx_new_font(data->font))
		return (free(data), NULL);
	data->font->color = 0x00FF00;
	data->font->screen = data->img;
	data->oldtime = 0;
	data->newtime = 0;
	data->frames = 0;
	data->fps = FPS;
	data->screen_width = WIDTH;
	data->screen_height = HEIGHT;
	data->player = malloc(sizeof(t_player));
	data->texture = malloc(sizeof(t_texture));
	data->key_state = init_key_state();
	return (data);
}

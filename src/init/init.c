/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:34:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/25 19:25:53 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static t_key_state	*init_key_state(void)
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

static t_mlx_img	*allocate_img(void *mlx)
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
	img->width = WIDTH;
	img->height = HEIGHT;
	return (img);
}

static t_main	*init_components(t_main *data)
{
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
	data->fps_max = 0;
	data->fps_min = FPS;
	data->fps = FPS;
	data->screen_width = WIDTH;
	data->screen_height = HEIGHT;
	data->player = malloc(sizeof(t_player));
	data->textures = malloc(sizeof(t_texture));
	data->key_state = init_key_state();
	if (parse_map(data, "assets/map.cub"))
		return (free_data(data), NULL);
	if (!init_textures(data)
		|| !data->player || !data->textures || !data->key_state)
		return (free_data(data), NULL);
	return (data);
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
	return (init_components(data));
}

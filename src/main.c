/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/24 21:56:27 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_textures(t_main *data)
{
	if (!data->textures)
		return ;
	if (data->textures->north)
	{
		mlx_destroy_image(data->mlx, data->textures->north->img);
		free(data->textures->north);
	}
	if (data->textures->south)
	{
		mlx_destroy_image(data->mlx, data->textures->south->img);
		free(data->textures->south);
	}
	if (data->textures->west)
	{
		mlx_destroy_image(data->mlx, data->textures->west->img);
		free(data->textures->west);
	}
	if (data->textures->east)
	{
		mlx_destroy_image(data->mlx, data->textures->east->img);
		free(data->textures->east);
	}
	free(data->textures->north_path);
	free(data->textures->south_path);
	free(data->textures->west_path);
	free(data->textures->east_path);
	free(data->textures);
}

void	*free_data(t_main *data)
{
	if (!data)
		exit(0);
	free_textures(data);
	if (data->img)
	{
		if (data->img->img)
			mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
	}
	if (data->player)
		free(data->player);
	if (data->key_state)
		free(data->key_state);
	if (data->font)
		clear_mlx_font(data->font);
	if (data->map)
		free_tab((void **)data->map);
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
	}
	free(data->mlx);
	free(data);
	exit(0);
}

int	main(void)
{
	t_main		*data;

	data = init_main();
	if (!data || !data->player || !data->key_state || !data->textures)
		return (free_data(data), 1);
	data->start_time = get_time_ms();
	render_frame(data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
	mlx_hook(data->win, 17, 0, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

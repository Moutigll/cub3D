/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/26 20:24:14 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_t.h"

static void	free_textures(t_main *data)
{
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

void	cleanup_threads(t_thread_data *threads)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		threads[i].running = 0;
		i++;
	}
	i = 0;
	pthread_barrier_wait(threads[0].start);
	pthread_barrier_wait(threads[0].end);
	while (i < THREADS)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
	free(threads[0].start);
	free(threads[0].end);
	free(threads);
}

void	*free_data(t_main *data)
{
	cleanup_threads(data->threads);
	if (data->textures)
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

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	main(void)
{
	t_main			*data;

	data = init_main();
	if (!data || !data->player || !data->key_state || !data->textures)
		return (free_data(data), 1);
	data->threads = init_threads(data);
	data->start_time = get_time_ms();
	render_frame(data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
	if (ENABLE_MOUSE == True)
		mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 0, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

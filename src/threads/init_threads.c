/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:35:43 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/26 20:46:49 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_t.h"

void	handle_thread_render(t_thread_data *thread_data, int start_x, int end_x)
{
	int		x;
	double	camera_x;

	while (thread_data->running)
	{
		pthread_barrier_wait(thread_data->start);
		if (!thread_data->running)
		{
			pthread_barrier_wait(thread_data->end);
			break ;
		}
		x = start_x;
		while (x < end_x)
		{
			camera_x = 2 * x / (double)thread_data->data->screen_width - 1;
			cast_ray(thread_data->data, camera_x, x);
			x++;
		}
		pthread_barrier_wait(thread_data->end);
	}
}

void	*thread_render(void *arg)
{
	t_thread_data	*thread_data;
	int				start_x;
	int				end_x;

	thread_data = (t_thread_data *)arg;
	start_x = (thread_data->data->screen_width / THREADS)
		* thread_data->thread_id;
	end_x = (thread_data->data->screen_width / THREADS)
		* (thread_data->thread_id + 1);
	handle_thread_render(thread_data, start_x, end_x);
	return (NULL);
}

void	init_thread_data(t_thread_data *threads, t_main *data,
		pthread_barrier_t *start, pthread_barrier_t *end)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		threads[i].data = data;
		threads[i].thread_id = i;
		threads[i].start = start;
		threads[i].end = end;
		threads[i].running = 1;
		if (pthread_create(&threads[i].thread,
				NULL, thread_render, (void *)&threads[i]) != 0)
		{
			perror("Error: Failed to create thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

t_thread_data	*init_threads(t_main *data)
{
	t_thread_data		*threads;
	pthread_barrier_t	*start;
	pthread_barrier_t	*end;

	threads = malloc(sizeof(t_thread_data) * THREADS);
	if (!threads)
	{
		perror("Error: Failed to allocate memory for thread data");
		exit(EXIT_FAILURE);
	}
	start = malloc(sizeof(pthread_barrier_t));
	end = malloc(sizeof(pthread_barrier_t));
	if (!start || !end)
	{
		perror("Error: Failed to allocate memory for barriers");
		exit(EXIT_FAILURE);
	}
	pthread_barrier_init(start, NULL, THREADS + 1);
	pthread_barrier_init(end, NULL, THREADS + 1);
	init_thread_data(threads, data, start, end);
	return (threads);
}

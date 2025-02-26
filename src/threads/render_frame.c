/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:50:15 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/26 19:09:35 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D_t.h"

void	render_frame(t_main *data)
{
	t_thread_data	*threads;

	threads = data->threads;
	pthread_barrier_wait(threads[0].start);
	pthread_barrier_wait(threads[0].end);
	if (DEBUG_MODE == True)
		render_debug_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:09:33 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/22 23:17:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	render_frame(t_main *data)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < data->screen_width)
	{
		camera_x = 2 * x / (double)data->screen_width - 1;
		cast_ray(data, camera_x, x);
		x++;
	}
	if (DEBUG_MODE == True)
		render_debug_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

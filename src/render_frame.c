/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:09:33 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/22 17:50:29 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	fill_background(t_main *data)
{
	int		ceiling_color;
	int		floor_color;
	char	*pixel;
	int		x;
	int		y;

	ceiling_color = data->textures->ceiling_color;
	floor_color = data->textures->floor_color;
	y = 0;
	pixel = data->img->addr;
	while (y < data->screen_height)
	{
		x = 0;
		while (x < data->screen_width)
		{
			if (y < data->screen_height / 2)
				*(unsigned int *)pixel = ceiling_color;
			else
				*(unsigned int *)pixel = floor_color;
			pixel += (data->img->bpp / 8);
			x++;
		}
		y++;
	}
}

void	render_frame(t_main *data)
{
	int		x;
	double	camera_x;

	fill_background(data);
	x = 0;
	while (x < data->screen_width)
	{
		camera_x = 2 * x / (double)data->screen_width - 1;
		cast_ray(data, camera_x);
		x++;
	}
	if (DEBUG_MODE == True)
		render_debug_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

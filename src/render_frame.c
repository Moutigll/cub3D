/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:09:33 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 22:07:29 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*Temporary function no need to orm the code*/

void	draw_line(t_main *data, int x1, int y1, int x2, int y2, int color)
{
	int	dx = abs(x2 - x1);
	int	dy = abs(y2 - y1);
	int	sx = (x1 < x2) ? 1 : -1;
	int	sy = (y1 < y2) ? 1 : -1;
	int	err = dx - dy;
	int	e2;

	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	rotate_player(t_main *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->cam_plane_x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	data->player->dir_x = old_dir_x * cos_a - data->player->dir_y * sin_a;
	data->player->dir_y = old_dir_x * sin_a + data->player->dir_y * cos_a;
	data->player->cam_plane_x = old_plane_x
		* cos_a - data->player->cam_plane_y * sin_a;
	data->player->cam_plane_y = old_plane_x
		* sin_a + data->player->cam_plane_y * cos_a;
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
}

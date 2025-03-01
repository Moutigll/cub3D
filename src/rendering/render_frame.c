/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:09:33 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/01 18:22:16 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	if (MINIMAP == True)
		draw_minimap(data, 10, 300, 10);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

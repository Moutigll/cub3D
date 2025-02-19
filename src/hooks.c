/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:30 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 21:48:00 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_hook(int keycode, t_main *data)
{
	if (keycode == KEY_ESC)
		free_data(data);
	return (0);
}

int	destroy_hook(t_main *data)
{
	free_data(data);
	return (0);
}

/* Main loop where we run and refresh the game*/

int	loop_hook(t_main *data)
{
	data->newtime = get_time_ms();
	if (data->newtime - data->oldtime >= 1000 / FPS)
	{
		rotate_player(data, 0.01);
		mlx_clear_window(data->mlx, data->win);
		render_frame(data);
		data->oldtime = data->newtime;
	}
	return (0);
}

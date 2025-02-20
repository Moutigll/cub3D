/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:30 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 15:11:12 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press_hook(int keycode, t_main *data)
{
	if (keycode == KEY_ESC)
		free_data(data);
	if (keycode == KEY_LEFT)
		data->key_state->left = True;
	if (keycode == KEY_RIGHT)
		data->key_state->right = True;
	if (keycode == KEY_UP)
		data->key_state->up = True;
	if (keycode == KEY_DOWN)
		data->key_state->down = True;
	return (0);
}

int	key_release_hook(int keycode, t_main *data)
{
	if (keycode == KEY_LEFT)
		data->key_state->left = False;
	if (keycode == KEY_RIGHT)
		data->key_state->right = False;
	if (keycode == KEY_UP)
		data->key_state->up = False;
	if (keycode == KEY_DOWN)
		data->key_state->down = False;
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
		mlx_clear_window(data->mlx, data->win);
		main_loop(data);
		render_frame(data);
		data->oldtime = data->newtime;
	}
	return (0);
}

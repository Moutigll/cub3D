/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:30 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 09:46:49 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press_hook(int keycode, t_main *data)
{
	if (keycode == KEY_ESC)
		free_data(data);
	if (keycode == KEY_LEFT || keycode == KEY_A)
		data->key_state->left = True;
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		data->key_state->right = True;
	if (keycode == KEY_UP || keycode == KEY_W)
		data->key_state->up = True;
	if (keycode == KEY_DOWN || keycode == KEY_S)
		data->key_state->down = True;
	if (keycode == KEY_P)
		print_data(data);
	if (keycode == KEY_PLUS && data->player->fov < 175)
		data->player->fov += 5;
	if (keycode == KEY_MINUS && data->player->fov > 5)
		data->player->fov -= 5;
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
	{
		data->player->cam_plane_x = tan((data->player->fov * PI / 180.0) / 2.0);
		data->player->cam_plane_y = tan((data->player->fov * PI / 180.0) / 2.0);
	}
	return (0);
}

int	key_release_hook(int keycode, t_main *data)
{
	if (keycode == KEY_LEFT || keycode == KEY_A)
		data->key_state->left = False;
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		data->key_state->right = False;
	if (keycode == KEY_UP || keycode == KEY_W)
		data->key_state->up = False;
	if (keycode == KEY_DOWN || keycode == KEY_S)
		data->key_state->down = False;
	return (0);
}

int	destroy_hook(t_main *data)
{
	free_data(data);
	return (0);
}

int	loop_hook(t_main *data)
{
	unsigned int	current_time;

	current_time = get_time_ms();
	if (current_time - data->newtime >= 1000 / FPS)
	{
		data->oldtime = data->newtime;
		data->newtime = current_time;
		main_loop(data);
		render_frame(data);
	}
	return (0);
}

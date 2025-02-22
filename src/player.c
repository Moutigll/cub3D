/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:13:22 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/22 01:28:31 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_player(t_main *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;
	double	adjusted_angle;

	if (data->fps > 0)
		adjusted_angle = angle * (60.0 / data->fps);
	else
		adjusted_angle = angle;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->cam_plane_x;
	cos_a = cos(adjusted_angle);
	sin_a = sin(adjusted_angle);
	data->player->dir_x = old_dir_x * cos_a - data->player->dir_y * sin_a;
	data->player->dir_y = old_dir_x * sin_a + data->player->dir_y * cos_a;
	data->player->cam_plane_x = old_plane_x
		* cos_a - data->player->cam_plane_y * sin_a;
	data->player->cam_plane_y = old_plane_x
		* sin_a + data->player->cam_plane_y * cos_a;
}

int	check_collision(t_main *data, double new_x, double new_y)
{
	int	x;
	int	y;

	x = (int)(data->player->player_x + new_x);
	y = (int)(data->player->player_y + new_y);
	if (data->map[y][x] != '0')
		return (1);
	return (0);
}

void	move_player(t_main *data, int direction)
{
	double	adjusted_speed;
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = MOVE_SPEED * direction;
	if (data->fps > 0)
		adjusted_speed = move_speed * (60.0 / data->fps);
	else
		adjusted_speed = move_speed;
	new_x = data->player->dir_x * adjusted_speed;
	new_y = data->player->dir_y * adjusted_speed;
	if (!check_collision(data, new_x, 0))
		data->player->player_x += new_x;
	if (!check_collision(data, 0, new_y))
		data->player->player_y += new_y;
}

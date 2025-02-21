/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:13:22 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 21:46:24 by ele-lean         ###   ########.fr       */
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
	data->player->cam_plane_x = old_plane_x * cos_a - data->player->cam_plane_y * sin_a;
	data->player->cam_plane_y = old_plane_x * sin_a + data->player->cam_plane_y * cos_a;
}


void	move_player(t_main *data, int direction)
{
	double	adjusted_speed;
	double	move_speed;

	move_speed = MOVE_SPEED * direction;
	if (data->fps > 0)
		adjusted_speed = move_speed * (60.0 / data->fps);
	else
		adjusted_speed = move_speed;
	data->player->player_x += data->player->dir_x * adjusted_speed;
	data->player->player_y += data->player->dir_y * adjusted_speed;

}

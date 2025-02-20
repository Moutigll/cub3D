/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:13:22 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 15:52:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	move_player(t_main *data, int direction)
{
	double	move_speed;

	move_speed = MOVE_SPEED * direction;
	data->player->player_x += data->player->dir_x * move_speed;
	data->player->player_y += data->player->dir_y * move_speed;
}

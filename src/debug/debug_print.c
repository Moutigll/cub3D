/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:59:55 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/23 01:01:57 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	print_map(t_main *data)
{
	int	y;

	y = 0;
	printf("\tMap:\n");
	data->map[(int)data->player->player_y][(int)data->player->player_x] = 'P';
	while (data->map[y])
	{
		printf("\t\t|%s|\n", data->map[y]);
		y++;
	}
	data->map[(int)data->player->player_y][(int)data->player->player_x] = '0';
	printf("\n\t\tCeiling color: %d\n", data->textures->ceiling_color);
	printf("\t\tFloor color: %d\n", data->textures->floor_color);
}

static void	print_player(t_player *player)
{
	printf("\tPlayer:\n\t\tPlayer x: %f\n", player->player_x);
	printf("\t\tPlayer y: %f\n", player->player_y);
	printf("\t\tDir x: %f\n", player->dir_x);
	printf("\t\tDir y: %f\n", player->dir_y);
	printf("\t\tCam plane x: %f\n", player->cam_plane_x);
	printf("\t\tCam plane y: %f\n", player->cam_plane_y);
	printf("\t\tFOV: %f\n", player->fov);
}

static void	print_settings(t_main *data)
{
	printf("---------------------------------------------------------------\n");
	printf("DEBUG INFO:\n\tWindows\n");
	printf("\t\tWindow width: %d\n", data->screen_width);
	printf("\t\tWindow height: %d\n", data->screen_height);
	printf("\t\tTitle: %s\n", TITLE);
	printf("\t\tFPS: %d\n", FPS);
	printf("\t\tOld time: %d\n", data->oldtime);
	printf("\t\tNew time: %d\n", data->newtime);
}

void	print_data(t_main *data)
{
	print_settings(data);
	print_player(data->player);
	print_map(data);
}

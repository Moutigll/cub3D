/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:34:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 18:36:42 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_main	*init_main(void)
{
	t_main	*data;

	data = malloc(sizeof(t_main));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (NULL);
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
	{
		free(data);
		return (NULL);
	}
	data->oldtime = 0;
	data->newtime = 0;
	data->map = NULL;
	return (data);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->player_x = 0;
	player->player_y = 0;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->fov = 90;
	player->cam_plane_x = -player->dir_y * player->fov;
	player->cam_plane_y = player->dir_x * player->fov;
	return (player);
}

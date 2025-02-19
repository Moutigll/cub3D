/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 18:34:45 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_window(t_main *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free(data);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_main *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

int	destroy_hook(t_main *data)
{
	close_window(data);
	return (0);
}

int	main(void)
{
	t_main		*data;
	t_player	*player;

	data = init_main();
	if (!data)
	{
		write(1, "Error: Failed to initialize main data\n", 39);
		return (1);
	}
	player = init_player();
	if (!player)
	{
		write(1, "Error: Failed to initialize player\n", 37);
		free(data);
		return (1);
	}

	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

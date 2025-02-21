/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 09:01:02 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*free_data(t_main *data)
{
	if (!data)
		exit(0);
	if (data->img)
	{
		if (data->img->img)
			mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free_tab((void **)data->map);
	free(data->player);
	free(data);
	exit(0);
	return (NULL);
}

int	main(void)
{
	t_main		*data;

	data = init_main();
	if (!data || !data->player || !data->key_state || !data->texture)
		return (free_data(data), 1);
	if (parse_map(data, "assets/map.cub") == -1)
		return (free_data(data), 1);
	data->start_time = get_time_ms();
	render_frame(data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
	mlx_hook(data->win, 17, 0, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

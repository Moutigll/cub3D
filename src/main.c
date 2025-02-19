/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:59 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 21:50:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*free_data(t_main *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free_tab((void **)data->map);
	free(data);
	exit(0);
	return (NULL);
}

int	main(void)
{
	t_main		*data;

	data = init_main();
	if (!data || !data->player)
		return (free_data(data), 1);
	parse_map(data, "assets/map.cub");
	render_frame(data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

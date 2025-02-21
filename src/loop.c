/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:09:58 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 08:56:26 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main_loop(t_main *data)
{
	data->frames++;
	if (data->key_state->left)
		rotate_player(data, -ROTATE_SPEED);
	if (data->key_state->right)
		rotate_player(data, ROTATE_SPEED);
	if (data->key_state->up)
		move_player(data, 1);
	if (data->key_state->down)
		move_player(data, -1);
	return (0);
}

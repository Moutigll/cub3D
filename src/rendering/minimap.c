/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:16:03 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/01 19:40:34 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static unsigned int	get_pixel_color(t_main *data, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0 || x >= data->img->width || y >= data->img->height)
		return (0);
	src = data->img->addr
		+ (y * data->img->size_line + x * (data->img->bpp / 8));
	return (*(unsigned int *)src);
}

static unsigned int	blend_colors(unsigned int old_color, unsigned int new_color)
{
	unsigned char	new_chan[3];
	unsigned char	old_chan[3];
	unsigned char	alpha;
	int				i;

	alpha = (new_color >> 24) & 0xFF;
	new_chan[0] = (new_color >> 16) & 0xFF;
	new_chan[1] = (new_color >> 8) & 0xFF;
	new_chan[2] = new_color & 0xFF;
	old_chan[0] = (old_color >> 16) & 0xFF;
	old_chan[1] = (old_color >> 8) & 0xFF;
	old_chan[2] = old_color & 0xFF;
	i = 0;
	while (i < 3)
	{
		new_chan[i] = ((new_chan[i] * alpha)
				+ (old_chan[i] * (255 - alpha))) / 255;
		i++;
	}
	return ((new_chan[0] << 16) | (new_chan[1] << 8) | new_chan[2]);
}

static void	put_pixel_to_image(t_main *data, int x, int y, int color)
{
	char			*dst;
	unsigned int	old_color;
	unsigned int	final_color;

	if (x < 0 || y < 0 || x >= data->img->width || y >= data->img->height)
		return ;
	old_color = get_pixel_color(data, x, y);
	final_color = blend_colors(old_color, color);
	dst = data->img->addr + (y * data->img->size_line
			+ x * (data->img->bpp / 8));
	*(unsigned int *)dst = final_color;
}

static void	draw_square(t_main *data, t_square *sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq->size)
	{
		j = 0;
		while (j < sq->size)
		{
			put_pixel_to_image(data, sq->x + j, sq->y + i, sq->color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_main *data, int x, int y, int size)
{
	int			i;
	int			j;
	int			color;
	t_square	sq;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			color = DARK_PURPLE;
			if ((int)data->player->player_x == j
				&& (int)data->player->player_y == i)
				color = GREEN;
			else if (data->map[i][j] == '1')
				color = BLACK;
			else if (data->map[i][j] == '0')
				color = WHITE;
			else if (data->map[i][j] == '2')
				color = PURPLE;
			color = (color & 0xFFFFFF) | (MINIMAP_TRANSPARENCY << 24);
			sq.x = x + j * size;
			sq.y = y + i * size;
			sq.size = size;
			sq.color = color;
			draw_square(data, &sq);
			j++;
		}
		i++;
	}
}

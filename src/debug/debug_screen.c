/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 07:34:16 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/22 23:11:16 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*get_string(char *label, double value)
{
	char	*str;
	char	*value_str;

	value_str = ft_dtoa(value, 2);
	str = ft_strjoin_free(label, value_str, 0, 1);
	return (str);
}

static int	get_color_from_fps(float fps, float fps_min, float fps_max)
{
	float	factor;
	int		red;
	int		green;
	int		blue;

	factor = (fps - fps_min) / (fps_max - fps_min);
	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	if (factor <= 0.5)
	{
		red = 255;
		green = (int)(factor * 2 * 255);
		blue = 0;
	}
	else
	{
		red = (int)((1 - factor) * 255);
		green = 255;
		blue = 0;
	}
	return ((red << 16) | (green << 8) | blue);
}

static void	render_debug_screen_part2(t_main *data)
{
	char	*str;
	char	*tmp;

	ft_mlx_put_string(data->font, "Player: ", 10, 100);
	str = ft_strjoin_free("FOV: ", ft_itoa(data->player->fov), 0, 1);
	ft_mlx_put_string(data->font, str, 75, 125);
	free(str);
	str = get_string("X: ", data->player->player_x);
	ft_mlx_put_string(data->font, str, 75, 150);
	free(str);
	str = get_string("Y: ", data->player->player_y);
	ft_mlx_put_string(data->font, str, 75, 175);
	free(str);
	tmp = get_string("Orientation: ", data->player->dir_x);
	str = ft_strjoin_free(tmp, "|", 1, 0);
	tmp = ft_dtoa(data->player->dir_y, 2);
	str = ft_strjoin_free(str, tmp, 1, 1);
	ft_mlx_put_string(data->font, str, 75, 200);
	free(str);
	tmp = get_string("Plane: ", data->player->cam_plane_x);
	str = ft_strjoin_free(tmp, "|", 1, 0);
	tmp = ft_dtoa(data->player->cam_plane_y, 2);
	str = ft_strjoin_free(str, tmp, 1, 1);
	ft_mlx_put_string(data->font, str, 75, 225);
	free(str);
}

void	render_debug_screen(t_main *data)
{
	char	*str;
	char	*tmp;
	int		i;

	data->font->font_size = 4;
	data->font->space_width = 7;
	data->font->letter_spacing = 2;
	ft_mlx_put_string(data->font, "Debug screen: ON", 10, 10);
	data->font->font_size = 2;
	if (data->oldtime == 0)
		data->oldtime = get_time_ms();
	tmp = ft_dtoa(data->fps, 2);
	str = ft_strjoin_free("FPS: ", tmp, 0, 1);
	tmp = ft_strjoin_free(str, " | AVG: ", 1, 0);
	str = get_string(tmp, data->frames * 1000.0 / (data->newtime - data->start_time));
	free(tmp);
	tmp = ft_strjoin_free(str, " | Frames: ", 1, 0);
	str = ft_strjoin_free(tmp, ft_itoa(data->frames), 1, 1);
	data->font->color = get_color_from_fps(data->fps, data->fps_min, data->fps_max);
	ft_mlx_put_string(data->font, str, 10, 50);
	free(str);
	str = get_string("Worst: ", data->fps_min);
	data->font->color = 0xFF0000;
	i = ft_mlx_put_string(data->font, str, 10, 75);
	free(str);
	str = get_string(" | Best: ", data->fps_max);
	data->font->color = 0x00FF00;
	ft_mlx_put_string(data->font, str, i, 75);
	free(str);
	render_debug_screen_part2(data);
}

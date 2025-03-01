/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:02:48 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/01 22:41:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static t_mlx_img	*get_texture(t_main *data, t_ray *ray, int side)
{
	t_mlx_img	*texture;

	if (side == 0)
	{
		if (ray->ray_dir_x > 0)
			texture = data->textures->east;
		else
			texture = data->textures->west;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = data->textures->south;
		else
			texture = data->textures->north;
	}
	return (texture);
}

static void	draw_floor(t_main *data, unsigned int *pixel)
{
	while (pixel < data->max_addr)
	{
		*pixel = data->textures->floor_color;
		pixel += data->img_step;
	}
}

static void	draw_wall_line(t_main *data,
	int line_height, t_mlx_img *texture, t_params *params)
{
	int				draw_start;
	int				draw_end;
	int				y;
	unsigned int	*pixel;

	draw_start = -line_height / 2 + data->screen_height / 2;
	draw_end = line_height / 2 + data->screen_height / 2;
	y = 0;
	pixel = (unsigned int *)(data->img->addr + params->column);
	while (y < data->textures->middle && y < draw_start)
	{
		*pixel = data->textures->ceiling_color;
		pixel += data->img_step;
		y++;
	}
	while (y < draw_end && pixel < data->max_addr)
	{
		*pixel = *(unsigned int *)(texture->addr
				+ (((y - draw_start) * texture->height) / line_height)
				* texture->size_line + params->tex_x);
		pixel += data->img_step;
		y++;
	}
	draw_floor(data, pixel);
}

void	apply_texture(t_main *data, t_ray *ray, int side, int x)
{
	t_params	params;
	t_mlx_img	*texture;
	double		wall_x;
	int			tex_x;

	texture = get_texture(data, ray, side);
	if (side == 0)
		wall_x = data->player->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((side == 0 && ray->ray_dir_x > 0) || (side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	params.tex_x = tex_x * texture->bpp;
	params.column = x * (data->img->bpp / 8);
	draw_wall_line(data, (int)(data->screen_height
			/ ray->perp_wall_dist), texture, &params);
}

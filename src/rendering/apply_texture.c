/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:02:48 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/25 19:02:01 by ele-lean         ###   ########.fr       */
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

static void	draw_wall_line(t_main *data, int column, int line_height,
				t_mlx_img *texture, int tex_x)
{
	int				draw_start;
	int				draw_end;
	int				y;
	unsigned int	*pixel;
	int				step = data->img->size_line / 4;
	unsigned int	*max_addr;

	max_addr = (unsigned int *)(data->img->addr + data->img->size_line * data->screen_height);
	draw_start = -line_height / 2 + data->screen_height / 2;
	draw_end = line_height / 2 + data->screen_height / 2;
	y = 0;
	tex_x *= texture->bpp;
	pixel = (unsigned int *)(data->img->addr + column * (data->img->bpp / 8));
	while (y < data->textures->middle && y < draw_start)
	{
		*pixel = data->textures->ceiling_color;
		pixel += step;
		y++;
	}
	while (y < draw_end && pixel < max_addr)
	{
		*pixel = *(unsigned int *)(texture->addr
				+ (((y - draw_start) * texture->height) / line_height)
				* texture->size_line + tex_x);
		pixel += step;
		y++;
	}
	while (pixel < max_addr)
	{
		*pixel = data->textures->floor_color;
		pixel += step;
	}
}

void	apply_texture(t_main *data, t_ray *ray, int side, int x)
{
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
	draw_wall_line(data, x, (int)(data->screen_height
			/ ray->perp_wall_dist), texture, tex_x);
}

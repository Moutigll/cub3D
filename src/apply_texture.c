/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:02:48 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/22 19:54:19 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	mlx_pixel_put_img(t_main *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->img->width || y < 0 || y >= data->img->height)
		return ;
	dst = data->img->addr
		+ (y * data->img->size_line + x * (data->img->bpp / 8));
	*(int *)dst = color;
}

static void	draw_wall_line(t_main *data, int column, int line_height,
		t_mlx_img *texture, int tex_x)
{
	int	draw_start;
	int	draw_end;
	int	y;
	int	tex_y;
	int	color;

	draw_start = -line_height / 2 + data->screen_height / 2;
	draw_end = line_height / 2 + data->screen_height / 2;
	y = draw_start;
	if (y < 0)
		y = 0;
	while (y < draw_end && y < data->screen_height)
	{
		tex_y = ((y - draw_start) * texture->height) / line_height;
		color = *(int *)(texture->addr + (tex_y * (texture->size_line))
				+ (tex_x * (texture->bpp / 8)));
		mlx_pixel_put_img(data, column, y, color);
		y++;
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
	draw_wall_line(data, x, (int)(data->screen_height / ray->perp_wall_dist), texture, tex_x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:42:44 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 21:33:43 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	get_step_dir_and_size(t_ray *ray, t_main *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->size_x = (data->player->player_x - ray->ray_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->size_x = (ray->ray_x + 1.0 - data->player->player_x)
			* ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->size_y = (data->player->player_y - ray->ray_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->size_y = (ray->ray_y + 1.0 - data->player->player_y)
			* ray->delta_y;
	}
}

static t_ray	*init_cast_ray(t_main *data, double camera_x)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->ray_dir_x = data->player->dir_x
		+ (data->player->cam_plane_x * camera_x);
	ray->ray_dir_y = data->player->dir_y
		+ (data->player->cam_plane_y * camera_x);
	ray->ray_x = (int)data->player->player_x;
	ray->ray_y = (int)data->player->player_y;
	ray->delta_x = sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y)
			/ (ray->ray_dir_x * ray->ray_dir_x));
	ray->delta_y = sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x)
			/ (ray->ray_dir_y * ray->ray_dir_y));
	get_step_dir_and_size(ray, data);
	return (ray);
}

/*Temporary function to draw lines instead of textures*/

static void	draw_wall_line(t_main *data, int column, int line_height, int side)
{
	int	draw_start;
	int	draw_end;

	draw_start = -line_height / 2 + data->screen_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->screen_height / 2;
	if (draw_end >= data->screen_height)
		draw_end = data->screen_height - 1;
	if (side)
		draw_column(data, column, draw_start, draw_end, PURPLE);
	else
		draw_column(data, column, draw_start, draw_end, DARK_PURPLE);
}

void	cast_ray(t_main *data, double camera_x, int column)
{
	t_ray	*ray;
	double	perp_wall_dist;
	int		line_height;
	int		side;

	ray = init_cast_ray(data, camera_x);
	if (!ray)
		return ;
	while (data->map[ray->ray_y][ray->ray_x] == '0')
	{
		if (ray->size_x < ray->size_y)
		{
			ray->size_x += ray->delta_x;
			ray->ray_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->size_y += ray->delta_y;
			ray->ray_y += ray->step_y;
			side = 1;
		}
	}
	if (side == 0)
		perp_wall_dist = ray->size_x - ray->delta_x;
	else
		perp_wall_dist = ray->size_y - ray->delta_y;
	line_height = (int)(data->screen_height / perp_wall_dist);
	draw_wall_line(data, column, line_height, side);
	free(ray);
}

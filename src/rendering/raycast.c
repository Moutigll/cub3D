/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:42:44 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/23 01:04:29 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

static t_ray	*init_cast_ray(t_main *data, double camera_x, t_ray *ray)
{
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

void	cast_ray(t_main *data, double camera_x, int column)
{
	t_ray	ray;
	int		side;

	init_cast_ray(data, camera_x, &ray);
	while (data->map[ray.ray_y][ray.ray_x] == '0')
	{
		if (ray.size_x < ray.size_y)
		{
			ray.size_x += ray.delta_x;
			ray.ray_x += ray.step_x;
			side = 0;
		}
		else
		{
			ray.size_y += ray.delta_y;
			ray.ray_y += ray.step_y;
			side = 1;
		}
	}
	if (side == 0)
		ray.perp_wall_dist = ray.size_x - ray.delta_x;
	else
		ray.perp_wall_dist = ray.size_y - ray.delta_y;
	apply_texture(data, &ray, side, column);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:00:06 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 22:10:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>

// Window
# define WIDTH 800
# define HEIGHT 600
# define TITLE "Cub3D"
# define FPS 60

//Keycodes
# define KEY_ESC 65307

// Various
# define FISHEYE_CORRECTION 1

typedef struct s_player	t_player;
typedef struct s_main
{
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	void		*img;
	int			oldtime;
	int			newtime;
	char		**map;
	t_player	*player;
}	t_main;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	cam_plane_x;
	double	cam_plane_y;
	int		fov;
}	t_player;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		ray_x;
	int		ray_y;
	double	delta_x;
	double	delta_y;
	double	size_x;
	double	size_y;
	int		step_x;
	int		step_y;
}	t_ray;

// main.c
void		*free_data(t_main *data);

// init.c
t_main		*init_main(void);
t_player	*init_player(void);

// parse_map.c

void		parse_map(t_main *data, const char *file_path);

// hooks.c
int			key_hook(int keycode, t_main *data);
int			destroy_hook(t_main *data);
int			loop_hook(t_main *data);

// raycast.c

void		cast_ray(t_main *data, double camera_x, int column);

// render_frame.c

void		draw_line(t_main *data, int x1, int y1, int x2, int y2, int color);
long		get_time_ms(void);
void		rotate_player(t_main *data, double angle);
void		render_frame(t_main *data);

#endif
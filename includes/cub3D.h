/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:00:06 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 15:40:48 by ele-lean         ###   ########.fr       */
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
# define WIDTH 1920
# define HEIGHT 1080
# define TITLE "Cub3D"
# define FPS 60

//Keycodes
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

// Player
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.05

// Colors

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define PURPLE 0xFF00FF
# define DARK_PURPLE 0x800080

// Various
# define FISHEYE_CORRECTION 1

typedef enum e_bool
{
	False = 0,
	True = 1
}	t_bool;

typedef struct s_player		t_player;
typedef struct s_key_state	t_key_state;
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
	t_key_state	*key_state;
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

typedef struct s_key_state
{
	t_bool	left;
	t_bool	right;
	t_bool	up;
	t_bool	down;
}	t_key_state;

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
int			key_press_hook(int keycode, t_main *data);
int			key_release_hook(int keycode, t_main *data);
int			destroy_hook(t_main *data);
int			loop_hook(t_main *data);

// raycast.c
void		cast_ray(t_main *data, double camera_x, int column);

// loop.c
int			main_loop(t_main *data);

// player.c
void		rotate_player(t_main *data, double angle);
void		move_player(t_main *data, int direction);

// render_frame.c
void		draw_line(t_main *data, int x1, int y1, int x2, int y2, int color);
long		get_time_ms(void);
void		render_frame(t_main *data);

#endif
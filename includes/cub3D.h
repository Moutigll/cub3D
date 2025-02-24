/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:00:06 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/24 15:53:22 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

// Window
# define WIDTH 1920
# define HEIGHT 1080
# define TITLE "Cub3D"
# define FPS 60
# define DEBUG_MODE True

//Keycodes
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_PLUS 61
# define KEY_MINUS 45

// Player
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.05
# define FOV 45

// Colors

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define PURPLE 0xFF00FF
# define DARK_PURPLE 0x800080

// Various
# define FISHEYE_CORRECTION 1
# define HEX "0123456789ABCDEF"
# define PI 3.141592653589793238462643383279502884197169399375105820974944592308

typedef enum e_bool
{
	False = 0,
	True = 1
}	t_bool;

typedef struct s_player		t_player;
typedef struct s_key_state	t_key_state;
typedef struct s_texture	t_texture;
typedef struct s_mlx_img	t_mlx_img;
typedef struct s_main
{
	void		*mlx;
	void		*win;
	t_mlx_img	*img;
	double		fps;
	int			screen_width;
	int			screen_height;
	int			oldtime;
	int			newtime;
	long int	frames;
	int			start_time;
	char		**map;
	t_mlx_font	*font;
	t_player	*player;
	t_key_state	*key_state;
	t_texture	*textures;
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

typedef struct s_texture
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			floor_color;
	int			ceiling_color;
	t_mlx_img	*north;
	t_mlx_img	*south;
	t_mlx_img	*west;
	t_mlx_img	*east;
}	t_texture;

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
	double	perp_wall_dist;
}	t_ray;

// main.c
void		*free_data(t_main *data);

// init.c
t_main		*init_main(void);
void		init_player(t_player *player, int x, int y, char dir);

// parse_map.c
int			parse_map(t_main *data, const char *file_path);

// hooks.c
int			key_press_hook(int keycode, t_main *data);
int			key_release_hook(int keycode, t_main *data);
int			destroy_hook(t_main *data);
int			loop_hook(t_main *data);

// raycast.c
void		cast_ray(t_main *data, double camera_x);

// apply_texture.c
void		apply_texture(t_main *data, t_ray *ray, int side, int x);

// loop.c
int			main_loop(t_main *data);

// player.c
void		rotate_player(t_main *data, double angle);
void		move_player(t_main *data, int direction);

// render_frame.c
long		get_time_ms(void);
void		render_frame(t_main *data);

// debug
void		print_data(t_main *data);
void		render_debug_screen(t_main *data);

//flood_fill
bool	map_is_flooded(char **map);
void	flood_fill(t_main *data, char **map_cp, int x, int y);
char	**cpy_map(char **map);

#endif
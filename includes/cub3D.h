/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:00:06 by ele-lean          #+#    #+#             */
/*   Updated: 2025/03/01 22:41:51 by ele-lean         ###   ########.fr       */
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
# define FPS 1000
# define DEBUG_MODE True
# define MINIMAP True
# define MINIMAP_TRANSPARENCY 0xa0

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
# define KEY_PLUS 65451
# define KEY_MINUS 65453

// Player
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03
# define ENABLE_MOUSE True
# define MOUSE_SENSITIVITY 0.1
# define IGNORE_THRESHOLD 2
# define FOV 45

// Colors

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define PURPLE 0xFF00FF
# define GREEN 0x00FF00
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
	void			*mlx;
	void			*win;
	t_mlx_img		*img;
	double			fps;
	double			fps_min;
	double			fps_max;
	int				screen_width;
	int				screen_height;
	int				oldtime;
	int				newtime;
	long int		frames;
	int				start_time;
	char			**map;
	int				mouse_x;
	int				mouse_y;
	void			*threads;
	int				img_step;
	unsigned int	*max_addr;
	t_mlx_font		*font;
	t_player		*player;
	t_key_state		*key_state;
	t_texture		*textures;
}	t_main;

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	cam_plane_x;
	double	cam_plane_y;
	double	fov;
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
	int			middle;
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

typedef struct s_column
{
	int		x;
	int		column_height;
	int		draw_start;
	int		draw_end;
	int		step;
	int		y;
}	t_column;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_params
{
	int		tex_x;
	int		column;
}	t_params;

//main
void		*free_data(t_main *data);
long		get_time_ms(void);

//init
	//init_utils
int			init_textures(t_main *data);
t_mlx_font	*init_font(t_main *data);
void		init_player(t_player *player, int x, int y, char dir);
	//init
t_main		*init_main(void);

//parsing
	//parse_metadata
char		*parse_metadata(int fd, t_main *data);
int			get_max_line_length(char **map);
	//parse_map
int			parse_map(t_main *data, const char *file_path);
	//flood_fill
t_bool		map_is_flooded(char **map);
void		flood_fill(t_main *data, char **map_cp, int x, int y);
char		**cpy_map(char **map);

//rendering
	//render_frame
void		render_frame(t_main *data);
	//raycast
void		cast_ray(t_main *data, double camera_x, int column);
	//apply_texture
void		apply_texture(t_main *data, t_ray *ray, int side, int x);
	//minimap
void		draw_minimap(t_main *data, int x, int y, int size);

//hooks
int			key_press_hook(int keycode, t_main *data);
int			key_release_hook(int keycode, t_main *data);
int			destroy_hook(t_main *data);
int			loop_hook(t_main *data);
int			mouse_move(int x, int y, t_main *data);

//loop
int			main_loop(t_main *data);

//player
void		rotate_player(t_main *data, double angle);
void		move_player(t_main *data, int direction);

//debug
	//print
void		print_data(t_main *data);
	//screen
void		render_debug_screen(t_main *data);

#endif
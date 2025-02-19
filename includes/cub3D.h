/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:00:06 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/19 18:37:28 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

// Window
# define WIDTH 800
# define HEIGHT 600
# define TITLE "Cub3D"

//Keycodes
# define KEY_ESC 65307

typedef struct s_main
{
	void	*mlx;
	void	*win;
	int		screen_width;
	int		screen_height;
	int		oldtime;
	int		newtime;
	char	**map;
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

// init.c
t_main		*init_main(void);
t_player	*init_player(void);

#endif
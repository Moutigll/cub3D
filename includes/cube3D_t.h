/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D_t.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:32:39 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/26 19:30:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_T_H
# define CUBE3D_T_H

# include "cub3D.h"
# include <pthread.h>

# define THREADS 16

typedef struct s_thread_data
{
	t_main				*data;
	int					thread_id;
	pthread_barrier_t	*start;
	pthread_barrier_t	*end;
	pthread_t			thread;
	int					running;
}	t_thread_data;

t_thread_data	*init_threads(t_main *data);

#endif

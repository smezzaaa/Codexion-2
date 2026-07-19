/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 17:24:42 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/19 17:56:06 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct s_heap
{
	t_coder	*arr;
} t_heap;

typedef struct s_dongle
{
	int		available = 0;
	int		last_release = 0;
	pthread_mutex_t	d_mutex;
	pthread_cond_t	d_cond;
	t_heap	pq;
} t_dongle;

typedef struct s_coder
{
	int			id;
	int			last_compile;
	t_dongle	*r_dongle;
	t_dongle	l_dongle;
	pthread_t	t;
	t_compiler	compiler;
} t_coder;

typedef struct s_compiler
{
	int				n_coders;
	int				t_compile;
	int				t_burnout;
	int				t_debug;
	int				t_refactor;
	int				n_compiles;
	int 			d_cooldown;
	char			*scheduler;
	int				stop_flag;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		t_monitor;
	pthread_mutex_t	m_monitor;
	pthread_cond_t	c_monitor;
} t_compiler;

#endif
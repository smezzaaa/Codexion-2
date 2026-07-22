/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 17:24:42 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/22 12:54:01 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct s_coder t_coder;
typedef struct s_heap t_heap;
typedef struct s_dongle t_dongle;
typedef struct s_compiler t_compiler;

typedef struct s_heap
{
	t_coder	**arr;
} t_heap;

typedef struct s_dongle
{
	int		available;
	int		last_release;
	pthread_mutex_t	d_mutex;
	pthread_cond_t	d_cond;
	t_heap	*pq;
} t_dongle;

typedef struct s_coder
{
	int			id;
	int			last_compile;
	int			r_first;
	int			l_first;
	t_dongle	*r_dongle;
	t_dongle	*l_dongle;
	pthread_t	t;
	t_compiler	*compiler;
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
	t_coder			**coders;
	t_dongle		**dongles;
	pthread_t		t_monitor;
	pthread_mutex_t	m_monitor;
	pthread_cond_t	c_monitor;
} t_compiler;

int		create_pq(t_heap *pq);
void	fill_pq(int n_coders, t_coder **coders);
int		compiler_initializer(t_compiler *compiler, char **av);
int		coder_initializer(int n_coders, t_coder **coders, t_compiler *compiler);
int		dongle_initializer(int n_coders, t_dongle **dongles);
void	assign_dongle(int n_coders, t_coder **coders, t_dongle **dongles);
int		parser(char **av);
void	ft_cleanup(int n_coders, t_compiler *compiler);
void	swap_pq(t_heap *pq);
void	tidy_pq(int n_coders, t_coder **coders);
int		create_threads(t_compiler *compiler,t_coder **coders, int n_coders);
void	*coder_routine(void *arg);
void	manage_request(t_dongle	*dongle);

#endif
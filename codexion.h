/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 17:24:42 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/30 16:30:46 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

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
	bool			available;
	long long int		last_release;
	int				req;
	pthread_mutex_t	d_mutex;
	pthread_cond_t	d_cond;
	t_heap			*pq;
} t_dongle;

typedef struct s_coder
{
	int			id;
	int			compiles;
	int			i;
	long long int	last_compile;
	t_dongle	*r_dongle;
	t_dongle	*l_dongle;
	pthread_t	t;
	t_compiler	*compiler;
} t_coder;

typedef struct s_compiler
{
	int				n_coders;
	long long int		t_compile;
	long long int		t_burnout;
	long long int		t_debug;
	long long int		t_refactor;
	int				n_compiles;
	long long int		d_cooldown;
	char			*scheduler;
	bool			stop_flag;
	long long int		start;
	t_coder			**coders;
	t_dongle		**dongles;
	pthread_t		t_monitor;
	pthread_mutex_t	m_monitor;
	pthread_cond_t	c_monitor;
} t_compiler;

int			parser(char **av);
int			compiler_initializer(t_compiler *compiler, char **av);
bool		create_threads(t_coder **coders, int n_coders);
void		*coder_routine(void *arg);
void		take_dongles(t_coder *coder, t_dongle *dongle, long int d_cooldown);
void		ft_cleanup(int n_coders, t_compiler *compiler);
long long	gettime(long long start);
int			create_pq(t_heap *pq);
void		swap_pq(t_heap *pq);
void		push_coder(t_dongle *dongle, t_coder *coder);
void		pop_coder(t_heap *pq, t_coder *coder, t_dongle *dongle);
void		*monitor(void *arg);

#endif
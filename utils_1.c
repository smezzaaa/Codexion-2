/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:26:57 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:30:35 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	gettime(long long start)
{
	struct timeval	tv;
	long long		now;

	if (gettimeofday(&tv, NULL) == 0)
	{
		now = (long long)((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
		return (now - start);
	}
	return (0);
}

struct timespec	ft_timer(void)
{
	struct timeval	now;
	struct timespec	ts;

	gettimeofday(&now, NULL);
	ts.tv_sec = now.tv_sec;
	ts.tv_nsec = (now.tv_usec + 5000) * 1000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec += 1;
		ts.tv_nsec -= 1000000000;
	}
	return (ts);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	close_simulation(t_compiler *compiler)
{
	pthread_join(compiler->t_monitor, NULL);
	pthread_mutex_destroy(&compiler->m_log);
}

void	ft_cleanup(int n_coders, t_compiler *compiler)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		pthread_mutex_destroy(&compiler->dongles[i]->d_mutex);
		pthread_mutex_destroy(&compiler->coders[i]->m_coder);
		pthread_cond_destroy(&compiler->dongles[i]->d_cond);
		safe_free(compiler->coders[i]);
		safe_free(compiler->dongles[i]->pq->arr);
		safe_free(compiler->dongles[i]->pq);
		safe_free(compiler->dongles[i]);
		i++;
	}
	safe_free(compiler->coders);
	safe_free(compiler->dongles);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 20:22:50 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 13:43:58 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*edf_scheduler(t_coder *a, t_coder *b)
{
	long long	a_deadline;
	long long	b_deadline;

	pthread_mutex_lock(&a->m_coder);
	a_deadline = a->last_compile + a->compiler->t_burnout;
	pthread_mutex_unlock(&a->m_coder);
	pthread_mutex_lock(&b->m_coder);
	b_deadline = b->last_compile + b->compiler->t_burnout;
	pthread_mutex_unlock(&b->m_coder);
	if (a_deadline < b_deadline)
		return (a);
	if (a_deadline == b_deadline && a->id < b->id)
		return (a);
	return (b);
}

static t_coder	*fifo_scheduler(t_coder *a, t_coder *b)
{
	int	pos_a;
	int	pos_b;

	pthread_mutex_lock(&a->m_coder);
	pos_a = a->pos;
	pthread_mutex_unlock(&a->m_coder);
	pthread_mutex_lock(&b->m_coder);
	pos_b = b->pos;
	pthread_mutex_unlock(&b->m_coder);
	if (pos_a < pos_b)
		return (a);
	else
		return (b);
	// else
	// 	return (edf_scheduler(a, b));
}

static t_coder	*getfirst(t_dongle *dongle)
{
	t_coder	*a;
	t_coder	*b;

	if (dongle->req == 0)
		return (NULL);
	if (dongle->req == 1)
		return (dongle->pq->arr[0]);
	a = dongle->pq->arr[0];
	b = dongle->pq->arr[1];
	if (strcmp(a->compiler->scheduler, "fifo") == 0)
		return (fifo_scheduler(a, b));
	else if (strcmp(a->compiler->scheduler, "edf") == 0)
		return (edf_scheduler(a, b));
	return (NULL);
}

static void	takedongle_timestamp(t_coder *coder, t_dongle *dongle)
{
	if (dongle == coder->r_dongle)
		log_state(coder, "has taken right dongle");
	else
		log_state(coder, "has taken left dongle");
}

static bool	is_available(t_coder *c, t_dongle *d)
{
	long long	cool;

	cool = c->compiler->d_cooldown;
	if (!(d->available || d->pq->arr[0] == c))
		return (false);
	if (d->last_release == 0)
		return (true);
	return (d->last_release + cool < gettime(c->compiler->start));
}

bool	take_dongles(t_coder *c, t_dongle *d, long int d_cooldown)
{
	struct timespec	deadline;

	pthread_mutex_lock(&d->d_mutex);
	push_coder(d, c);
	while (!is_available(c, d))
	{
		deadline = ft_timer();
		pthread_cond_timedwait(&d->d_cond, &d->d_mutex, &deadline);
		if (is_stopped(c->compiler))
		{
			pthread_mutex_unlock(&d->d_mutex);
			return (false);
		}
	}
	takedongle_timestamp(c, d);
	d->available = false;
	pop_coder(d->pq, c, d);
	pthread_mutex_unlock(&d->d_mutex);
	return (true);
}

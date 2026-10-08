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

static void	push_pair(t_coder *c, t_dongle *f, t_dongle *s)
{
	pthread_mutex_lock(&f->d_mutex);
	pthread_mutex_lock(&s->d_mutex);
	push_coder(f, c);
	push_coder(s, c);
	pthread_mutex_unlock(&s->d_mutex);
	pthread_mutex_unlock(&f->d_mutex);
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

static bool	acquire_dongle(t_coder *c, t_dongle *f, t_dongle *s)
{
	bool	taken;

	taken = false;
	pthread_mutex_lock(&f->d_mutex);
	pthread_mutex_lock(&s->d_mutex);
	if (is_available(c, f) && is_available(c, s))
	{
		f->available = false;
		s->available = false;
		pop_coder(f->pq, c, f);
		pop_coder(s->pq, c, s);
		log_state(c, "has taken a dongle");
		log_state(c, "has taken a dongle");
		taken = true;
	}
	pthread_mutex_unlock(&s->d_mutex);
	pthread_mutex_unlock(&f->d_mutex);
	return (taken);
}

bool	take_dongles(t_coder *c, t_dongle *first, t_dongle *second)
{
	push_pair(c, first, second);
	while (!is_stopped(c->compiler))
	{
		if (acquire_dongle(c, first, second))
			return (true);
		usleep (500);
	}
	return (false);
}

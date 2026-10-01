/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 20:22:50 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/01 11:43:37 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_coder	*edf_scheduler(t_coder *a, t_coder *b)
{
	int	a_deadline;
	int	b_deadline;

	a_deadline = a->last_compile + a->compiler->t_burnout;
	b_deadline = b->last_compile + b->compiler->t_burnout;
	if (a_deadline < b_deadline)
		return (a);
	else
		return (b);
}

static t_coder	*fifo_scheduler(t_coder *a, t_coder *b)
{
	if (a->pos < b->pos)
		return (a);
	else if (a->pos > b->pos)
		return (b);
	else
		return (edf_scheduler(a, b));
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
		printf("%lld %d has taken right dongle\n",
			gettime(coder->compiler->start), coder->id);
	else
		printf("%lld %d has taken left dongle\n",
			gettime(coder->compiler->start), coder->id);
}

bool	take_dongles(t_coder *coder, t_dongle *dongle, long int d_cooldown)
{
	struct timespec	deadline;

	pthread_mutex_lock(&dongle->d_mutex);
	push_coder(dongle, coder);
	while (!((getfirst(dongle) == coder) && dongle->available
			&& ((dongle->last_release + d_cooldown)
				< gettime(coder->compiler->start)
				|| (dongle->last_release == 0)))
		&& (!coder->compiler->stop_flag))
	{
		deadline = ft_timer();
		pthread_cond_timedwait(&dongle->d_cond, &dongle->d_mutex, &deadline);
		if (coder->compiler->stop_flag)
		{
			pthread_mutex_unlock(&dongle->d_mutex);
			return (false);
		}
	}
	takedongle_timestamp(coder, dongle);
	dongle->available = false;
	pop_coder(dongle->pq, coder, dongle);
	pthread_mutex_unlock(&dongle->d_mutex);
	return (true);
}

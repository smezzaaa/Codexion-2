/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 20:22:50 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/31 15:04:01 by smeza-ro         ###   ########.fr       */
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
	{
		//printf("%d came before %d\n", a->id, b->id);
		return (a);
	}
	else if (a->pos > b->pos)
	{
		//printf("%d came before %d\n", b->id, a->id);
		return (b);
	}
	else
		return (edf_scheduler(a, b));
}

static t_coder	*getfirst(t_dongle *dongle)
{
	if (dongle->req == 0)
		return (NULL);
	if (dongle->req == 1)
		return (dongle->pq->arr[0]);
	t_coder	*a;
	t_coder	*b;

	a = dongle->pq->arr[0];
	b = dongle->pq->arr[1];
	if (strcmp(a->compiler->scheduler, "fifo") == 0)
		return (fifo_scheduler(a, b));
	else if (strcmp(a->compiler->scheduler, "edf") == 0)
		return (edf_scheduler(a, b));
	return (NULL);
}

void	take_dongles(t_coder *coder, t_dongle *dongle, long int d_cooldown)
{
	//if ((coder->compiles == 0) && (coder->id % 2 == 0))
	//	usleep(500);
	pthread_mutex_lock(&dongle->d_mutex);
	push_coder(dongle, coder);
	while (!((getfirst(dongle) == coder) && dongle->available
			&& ((dongle->last_release + d_cooldown) < gettime(coder->compiler->start)
			|| (dongle->last_release == 0))))
	{
		pthread_cond_wait(&dongle->d_cond, &dongle->d_mutex);
	}
	dongle->available = false;
	pop_coder(dongle->pq, coder, dongle);
	pthread_mutex_unlock(&dongle->d_mutex);
}

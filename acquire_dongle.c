/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_dongle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 20:22:50 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/28 18:47:57 by smeza-ro         ###   ########.fr       */
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
	if (a->i < b->i)
		return (a);
	else if (a->i > b->i)
		return (b);
	else
		return (edf_scheduler(a, b));
}

static t_coder	*getfirst(t_dongle *dongle)
{
	if (dongle->new_req == 0)
		return (NULL);
	if (dongle->new_req == 1)
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

//void	push_coder(t_dongle *dongle, t_coder *coder)
//{
//	dongle->pq->arr[dongle->new_req] = coder;
//	dongle->new_req += 1;
//}

void	take_dongles(t_coder *coder, t_dongle *dongle, long int d_cooldown)
{
	coder->i = dongle->new_req;
	pthread_mutex_lock(&dongle->d_mutex);
	dongle->new_req++;
	while (!(dongle->available
			|| ((dongle->last_release + d_cooldown) < gettime(coder->compiler->start))
			|| getfirst(dongle) == coder))
	{
		pthread_cond_wait(&dongle->d_cond, &dongle->d_mutex);
	}
	dongle->available = false;
	coder->compiler->stop_flag = true;
	pthread_mutex_unlock(&dongle->d_mutex);
}

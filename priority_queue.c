/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:46:24 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:37:56 by smeza-ro         ###   ########.fr       */
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

void	pop_coder(t_heap *pq, t_coder *coder, t_dongle *dongle)
{
	if (pq->arr[0] == coder)
	{
		pq->arr[0] = pq->arr[1];
		pq->arr[1] = NULL;
	}
	else
		pq->arr[1] = NULL;
	dongle->req -= 1;
}

void	push_coder(t_dongle *dongle, t_coder *c)
{
	dongle->req++;
	if (!dongle->pq->arr[0])
		dongle->pq->arr[0] = c;
	else
	{
		dongle->pq->arr[1] = c;
		if (strcmp(c->compiler->scheduler, "edf") == 0)
		{
			if (strcmp(c->compiler->scheduler, "edf") == 0
				&& c == edf_scheduler(c, dongle->pq->arr[0]))
				swap_pq(dongle->pq);
		}
	}
}

void	swap_pq(t_heap *pq)
{
	t_coder	*tmp;

	tmp = pq->arr[0];
	pq->arr[0] = pq->arr[1];
	pq->arr[1] = tmp;
}

bool	create_pq(t_heap *pq)
{
	pq->arr = (t_coder **)malloc(sizeof(t_coder *) * 2);
	if (!pq->arr)
		return (false);
	pq->arr = (t_coder **)memset(pq->arr, 0, (sizeof(t_coder *) * 2));
	return (true);
}

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

void	pop_coder(t_heap *pq, t_coder *coder, t_dongle *dongle)
{
	if (pq->arr[0] == coder)
	{
		pq->arr[0] = pq->arr[1];
		pq->arr[1] = NULL;
	}
	else
		pq->arr[1] = NULL;
	pthread_mutex_lock(&coder->m_coder);
	coder->pos = 0;
	pthread_mutex_unlock(&coder->m_coder);
	dongle->req -= 1;
	pthread_cond_broadcast(&dongle->d_cond);
}

void	push_coder(t_dongle *dongle, t_coder *coder)
{
	dongle->req++;
	pthread_mutex_lock(&coder->m_coder);
	coder->pos = dongle->next++;
	pthread_mutex_unlock(&coder->m_coder);
	if (!dongle->pq->arr[0])
		dongle->pq->arr[0] = coder;
	else
	{
		dongle->pq->arr[1] = coder;
		if (strcmp(coder->compiler->scheduler, "edf") == 0)
		{
			if (coder == edf_scheduler(coder, dongle->pq->arr[0]))
				swap_pq(dongle->pq);
		}
	}
	pthread_cond_broadcast(&dongle->d_cond);
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

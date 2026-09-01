/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:46:24 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/31 15:09:15 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//void	tidy_pq(int n_coders, t_coder **coders)
//{
//	int	i;
//
//	i = 0;
//	while (i < n_coders)
//	{
//		if (coders[i]->id % 2 != 0)
//			swap_pq(coders[i]->r_dongle->pq);
//		i++;
//	}
//}
//
//void	fill_pq(int n_coders, t_coder **coders)
//{
//	int	i;
//
//	i = 0;
//	while (i < n_coders)
//	{
//		coders[i]->l_dongle->pq->arr[0] = coders[i];
//		if (coders[i]->id == 1)
//			coders[i]->l_dongle->pq->arr[1] = coders[n_coders - 1];
//		else
//			coders[i]->l_dongle->pq->arr[1] = coders[i - 1];
//		i++;
//	}
//	tidy_pq(n_coders, coders);
//}

void	pop_coder(t_heap *pq, t_coder *coder, t_dongle *dongle)
{
	if (pq->arr[0] == coder)
	{
		if (pq->arr[1])
			swap_pq(pq);
		else
			pq->arr[0] = NULL;
	}
	pq->arr[1] = NULL;
	coder->pos = 0;
	dongle->req -= 1;
	//pthread_cond_broadcast(&dongle->d_cond);
}

void	push_coder(t_dongle *dongle, t_coder *coder)
{
	dongle->req++;
	coder->pos = dongle->next++;
	if (dongle->pq->arr[0] == NULL)
		dongle->pq->arr[0] = coder;
	else
		dongle->pq->arr[1] = coder;
	pthread_cond_broadcast(&dongle->d_cond);
}

void	swap_pq(t_heap *pq)
{
	t_coder	*tmp;

	tmp = pq->arr[0];
	pq->arr[0] = pq->arr[1];
	pq->arr[1]->pos = 1;
	tmp->pos = 2;
	pq->arr[1] = tmp;
}

int	create_pq(t_heap *pq)
{
	pq->arr = (t_coder **)malloc(sizeof(t_coder *) * 2);
	if (!pq->arr)
		return (1);
	pq->arr = (t_coder **)memset(pq->arr, 0, (sizeof(t_coder *) * 2));
	return (0);
}

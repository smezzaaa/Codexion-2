/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:46:24 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/22 11:55:09 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// caso numeri dispari: primo e ultimo coder restano senza un dongle!!
void	tidy_pq(int n_coders, t_coder **coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		if (coders[i]->id % 2 != 0)
			swap_pq(coders[i]->r_dongle->pq);
		i++;
	}
}

void	fill_pq(int n_coders, t_coder **coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		coders[i]->l_dongle->pq->arr[0] = coders[i];
		coders[i]->l_first = 1;
		if (coders[i]->id == 1)
			coders[i]->l_dongle->pq->arr[1] = coders[n_coders - 1];
		else
			coders[i]->l_dongle->pq->arr[1] = coders[i - 1];
		i++;
	}
	i = 0;
}

void	swap_pq(t_heap *pq)
{
	t_coder	*tmp;
	
	tmp = pq->arr[0];
	pq->arr[0] = pq->arr[1];
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
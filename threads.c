/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:12:46 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/22 12:55:51 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	manage_request(t_dongle *dongle)
{
	t_coder	*coder_a;
	t_coder	*coder_b;

	coder_a = dongle->pq->arr[0];
	coder_b = dongle->pq->arr[1];
	
}

int	create_threads(t_compiler *compiler,t_coder **coders, int n_coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		if (pthread_create(coders[i]->t, NULL, coder_routine, coders) != 0)
			return (1);
		i++;
	}
	while (i < n_coders)
	{
		if (pthread_join(coders[i]->t, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

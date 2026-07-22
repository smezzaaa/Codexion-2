/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:26:57 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/22 11:26:10 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// static void	ft_free_pq(t_heap	*h)
// {
// 	// free(h->arr[0]);
// 	// free(h->arr[1]);
// 	free(h);
// }

void safe_free(void *ptr) {
	if (ptr) {
		free(ptr);
	}
}

void	ft_cleanup(int n_coders, t_compiler *compiler)
{
	int	i;
	
	i = 0;
	while (i < n_coders)
	{
		safe_free(compiler->coders[i]);
		safe_free(compiler->dongles[i]->pq->arr);
		safe_free(compiler->dongles[i]->pq);
		pthread_mutex_destroy(&compiler->dongles[i]->d_mutex);
		pthread_cond_destroy(&compiler->dongles[i]->d_cond);
		safe_free(compiler->dongles[i]);
		i++;
	}
	safe_free(compiler->coders);
	safe_free(compiler->dongles);
	exit(0);
}
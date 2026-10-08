/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_case_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:01:02 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:36:41 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*one_coder_routine(void *arg)
{
	t_coder		*coder;
	t_dongle	*d;

	coder = (t_coder *)arg;
	d = coder->r_dongle;
	pthread_mutex_lock(&d->d_mutex);
	while (!is_stopped(coder->compiler))
		pthread_cond_wait(&d->d_cond, &d->d_mutex);
	pthread_mutex_unlock(&d->d_mutex);
	return (NULL);
}

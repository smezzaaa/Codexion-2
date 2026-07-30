/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:36:31 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/30 19:24:51 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//inizializzare compiler->start all'inizio della simulazione

bool	compiling(t_coder *coder, long int t_compile)
{
	if (usleep(t_compile * 1000) != 0)
		return (false);
	coder->compiles += 1;
	pthread_mutex_lock(&coder->l_dongle->d_mutex);
	coder->l_dongle->available = true;
	pthread_cond_broadcast(&coder->l_dongle->d_cond);
	pthread_mutex_unlock(&coder->l_dongle->d_mutex);
	pthread_mutex_lock(&coder->r_dongle->d_mutex);
	coder->r_dongle->available = true;
	pthread_cond_broadcast(&coder->r_dongle->d_cond);
	pthread_mutex_unlock(&coder->r_dongle->d_mutex);
	return(true);
}

bool	refactoring(long int t_refactor)
{
	if (usleep(t_refactor * 1000) != 0)
		return (false);
	return (true);
}

bool	debugging(long int t_debug)
{
	if (usleep(t_debug * 1000) != 0)
		return (false);
	return (true);
}

bool	release_dongle(t_dongle	*dongle, long int start, long int d_cooldown)
{
	if (usleep(d_cooldown * 1000) != 0)
		return (false);
	pthread_mutex_lock(&dongle->d_mutex);
	dongle->last_release = gettime(start) - (d_cooldown * 1000);
	pthread_cond_broadcast(&dongle->d_cond);
	pthread_mutex_unlock(&dongle->d_mutex);
	return (true);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!coder->compiler->stop_flag)
	{
		take_dongles(coder, coder->l_dongle, coder->compiler->d_cooldown);
		printf("%lld %d has taken left dongle\n", gettime(coder->compiler->start), coder->id);
		take_dongles(coder, coder->r_dongle, coder->compiler->d_cooldown);
		printf("%lld %d has taken right dongle\n", gettime(coder->compiler->start), coder->id);
		compiling(coder, coder->compiler->t_compile);
		printf("%lld %d is compiling\n", gettime(coder->compiler->start), coder->id);
		release_dongle(coder->l_dongle, coder->compiler->start, coder->compiler->d_cooldown);
		release_dongle(coder->r_dongle, coder->compiler->start, coder->compiler->d_cooldown);
		refactoring(coder->compiler->t_refactor);
		printf("%lld %d is refactoring\n", gettime(coder->compiler->start), coder->id);
		debugging(coder->compiler->t_refactor);
		printf("%lld %d is debugging\n", gettime(coder->compiler->start), coder->id);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:36:31 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/31 14:45:47 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//inizializzare compiler->start all'inizio della simulazione

static bool	compiling(t_coder *coder, long int t_compile)
{
	if (usleep(t_compile * 1000) != 0)
		return (false);
	coder->compiles += 1;
	return(true);
}

static bool	refactoring(long int t_refactor)
{
	if (usleep(t_refactor * 1000) != 0)
		return (false);
	return (true);
}

static bool	debugging(long int t_debug)
{
	if (usleep(t_debug * 1000) != 0)
		return (false);
	return (true);
}

static t_dongle	*get_next_dongle(t_coder *coder, t_dongle *dongle)
{
	if (dongle->id == coder->l_dongle->id)
		return (coder->l_dongle);
	else if (dongle->id == coder->r_dongle->id)
		return (coder->r_dongle);
	else
		return (NULL);
}

static bool	release_dongle(t_dongle	*dongle, long int start)
{
	pthread_mutex_lock(&dongle->d_mutex);
	dongle->available = true;
	dongle->last_release = gettime(start);
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
		take_dongles(coder, get_next_dongle(coder, coder->l_dongle), coder->compiler->d_cooldown);
		printf("%lld %d has taken left dongle\n", gettime(coder->compiler->start), coder->id);
		take_dongles(coder, get_next_dongle(coder, coder->r_dongle), coder->compiler->d_cooldown);
		printf("%lld %d has taken right dongle\n", gettime(coder->compiler->start), coder->id);
		coder->last_compile = gettime(coder->compiler->start);
		compiling(coder, coder->compiler->t_compile);
		printf("%lld %d is compiling\n", gettime(coder->compiler->start), coder->id);
		release_dongle(coder->l_dongle, coder->compiler->start);
		release_dongle(coder->r_dongle, coder->compiler->start);
		refactoring(coder->compiler->t_refactor);
		printf("%lld %d is refactoring\n", gettime(coder->compiler->start), coder->id);
		debugging(coder->compiler->t_refactor);
		printf("%lld %d is debugging\n", gettime(coder->compiler->start), coder->id);
	}
	return (NULL);
}

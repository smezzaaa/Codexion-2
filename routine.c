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

static bool	compiling(t_coder *coder, long int t_compile)
{
	coder->last_compile = gettime(coder->compiler->start);
	printf("%lld %d is compiling\n", gettime(coder->compiler->start), coder->id);
	if (usleep(t_compile * 1000) != 0)
		return (false);
	coder->compiles += 1;
	return(true);
}

static bool	refactoring(t_coder *coder, long int t_refactor)
{
	printf("%lld %d is refactoring\n", gettime(coder->compiler->start), coder->id);
	if (usleep(t_refactor * 1000) != 0)
		return (false);
	return (true);
}

static bool	debugging(t_coder *coder, long int t_debug)
{
	printf("%lld %d is debugging\n", gettime(coder->compiler->start), coder->id);
	if (usleep(t_debug * 1000) != 0)
		return (false);
	return (true);
}

static t_dongle	*get_first_dongle(t_coder *coder)
{
    if (coder->l_dongle->id < coder->r_dongle->id)
        return (coder->l_dongle);
    return (coder->r_dongle);
}

static t_dongle	*get_second_dongle(t_coder *coder)
{
    if (coder->l_dongle->id < coder->r_dongle->id)
        return (coder->r_dongle);
    return (coder->l_dongle);
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
		if (!take_dongles(coder, get_first_dongle(coder), coder->compiler->d_cooldown))
			return(NULL);
		printf("%lld %d has taken left dongle\n", gettime(coder->compiler->start), coder->id);
		if (!take_dongles(coder, get_second_dongle(coder), coder->compiler->d_cooldown))
			return(NULL);
		printf("%lld %d has taken right dongle\n", gettime(coder->compiler->start), coder->id);
		compiling(coder, coder->compiler->t_compile);
		release_dongle(coder->l_dongle, coder->compiler->start);
		release_dongle(coder->r_dongle, coder->compiler->start);
		if (coder->compiler->burnout_flag)
			break;
		refactoring(coder, coder->compiler->t_refactor);
		if (coder->compiler->burnout_flag)
			break;
		debugging(coder, coder->compiler->t_debug);
	}
	return (NULL);
}

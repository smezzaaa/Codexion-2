/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:51:00 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/01 12:03:54 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	compiling(t_coder *coder, long int t_compile)
{
	coder->last_compile = gettime(coder->compiler->start);
	printf("%lld %d is compiling\n",
		gettime(coder->compiler->start), coder->id);
	if (usleep(t_compile * 1000) != 0)
		return (false);
	coder->compiles += 1;
	return (true);
}

bool	refactoring(t_coder *coder, long int t_refactor)
{
	printf("%lld %d is refactoring\n",
		gettime(coder->compiler->start), coder->id);
	if (usleep(t_refactor * 1000) != 0)
		return (false);
	return (true);
}

bool	debugging(t_coder *coder, long int t_debug)
{
	printf("%lld %d is debugging\n",
		gettime(coder->compiler->start), coder->id);
	if (usleep(t_debug * 1000) != 0)
		return (false);
	return (true);
}

bool	release_dongle(t_dongle	*dongle, long int start)
{
	pthread_mutex_lock(&dongle->d_mutex);
	dongle->available = true;
	dongle->last_release = gettime(start);
	pthread_cond_broadcast(&dongle->d_cond);
	pthread_mutex_unlock(&dongle->d_mutex);
	return (true);
}

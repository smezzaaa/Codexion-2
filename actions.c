/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:51:00 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:07:42 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	compiling(t_coder *coder, long int t_compile)
{
	pthread_mutex_lock(&coder->m_coder);
	coder->last_compile = gettime(coder->compiler->start);
	pthread_mutex_unlock(&coder->m_coder);
	log_state(coder, "is compiling");
	if (usleep(t_compile * 1000) != 0)
		return (false);
	pthread_mutex_lock(&coder->m_coder);
	coder->compiles += 1;
	pthread_mutex_unlock(&coder->m_coder);
	return (true);
}

bool	refactoring(t_coder *coder, long int t_refactor)
{
	log_state(coder, "is refactoring");
	if (usleep(t_refactor * 1000) != 0)
		return (false);
	return (true);
}

bool	debugging(t_coder *coder, long int t_debug)
{
	log_state(coder, "is debugging");
	if (usleep(t_debug * 1000) != 0)
		return (false);
	return (true);
}

bool	release_dongle(t_coder *coder, long int start)
{
	pthread_mutex_lock(&coder->l_dongle->d_mutex);
	coder->l_dongle->available = true;
	coder->l_dongle->last_release = gettime(start);
	pthread_cond_broadcast(&coder->l_dongle->d_cond);
	pthread_mutex_unlock(&coder->l_dongle->d_mutex);
	pthread_mutex_lock(&coder->r_dongle->d_mutex);
	coder->r_dongle->available = true;
	coder->r_dongle->last_release = gettime(start);
	pthread_cond_broadcast(&coder->r_dongle->d_cond);
	pthread_mutex_unlock(&coder->r_dongle->d_mutex);
	return (true);
}

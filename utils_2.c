/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:36:10 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:10:03 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_coder *coder, char *mess)
{
	t_compiler	*c;
	
	c = coder->compiler;
	pthread_mutex_lock(&c->m_log);
	if (!c->stop_flag)
		printf("%lld %d %s\n", gettime(c->start), coder->id, mess);
	pthread_mutex_unlock(&c->m_log);
}

bool	is_stopped(t_compiler *c)
{
	bool	sf;
	pthread_mutex_lock(&c->m_log);
	sf = c->stop_flag;
	pthread_mutex_unlock(&c->m_log);
	return (sf);
}

void	set_stop(t_compiler *c)
{
	pthread_mutex_lock(&c->m_log);
	c->stop_flag = true;
	pthread_mutex_unlock(&c->m_log);
}

void	declare_burnout(t_compiler *c, int id)
{
	pthread_mutex_lock(&c->m_log);
	c->stop_flag = true;
	printf("%lld %d burned out\n", gettime(c->start), id);
	pthread_mutex_unlock(&c->m_log);
}
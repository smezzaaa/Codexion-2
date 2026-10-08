/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:53:14 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:28:51 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	check_n_compiles(t_compiler *compiler, t_coder **coders)
{
	int	i;
	int	done;

	i = 0;
	while (coders[i])
	{
		pthread_mutex_lock(&coders[i]->m_coder);
		done = coders[i]->compiles;
		pthread_mutex_unlock(&coders[i]->m_coder);
		if (done < compiler->n_compiles)
			return (false);
		i++;
	}
	return (true);
}

static int	check_burnout(t_compiler *c, t_coder **coders)
{
	int			i;
	long long	last_c;
	int			done;

	i = 0;
	while (coders[i])
	{
		pthread_mutex_lock(&coders[i]->m_coder);
		last_c = coders[i]->last_compile;
		done = coders[i]->compiles;
		pthread_mutex_unlock(&coders[i]->m_coder);
		if (last_c + c->t_burnout
			<= gettime(coders[i]->compiler->start)
			&& done < c->n_compiles)
		{
			return (coders[i]->id);
		}
		i++;
	}
	return (0);
}

static void	stop_simulation(t_dongle **dongles)
{
	int	i;

	i = 0;
	while (dongles[i])
	{
		pthread_mutex_lock(&dongles[i]->d_mutex);
		pthread_cond_broadcast(&dongles[i]->d_cond);
		pthread_mutex_unlock(&dongles[i]->d_mutex);
		i++;
	}
}

void	*monitor(void *arg)
{
	t_compiler	*compiler;
	int			id;

	compiler = (t_compiler *)arg;
	while (1)
	{
		id = check_burnout(compiler, compiler->coders);
		if (id)
		{
			declare_burnout(compiler, id);
			stop_simulation(compiler->dongles);
			break ;
		}
		if (check_n_compiles(compiler, compiler->coders))
		{
			set_stop(compiler);
			stop_simulation(compiler->dongles);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

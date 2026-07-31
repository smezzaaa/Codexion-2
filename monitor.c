/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:53:14 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/31 15:31:14 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	check_n_compiles(t_coder **coders)
{
	int	i;
	long long	compiles;

	i = 0;
	compiles = coders[0]->compiler->n_compiles;
	while (coders[i])
	{
		if (coders[i]->compiles <= compiles)
			return (false);
		i++;
	}
	return (true);
}

static bool	check_bornout(t_coder **coders)
{
	int	i;
	long long	bornout;

	i = 0;
	bornout = coders[0]->compiler->t_burnout;
	while (coders[i])
	{
		if ((coders[i]->last_compile + bornout) <= gettime(coders[i]->compiler->start))
		{
			printf("%lld %d burned out\n", gettime(coders[i]->compiler->start), coders[i]->id);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	stop_simulation(t_dongle **dongles)
{
	int	i;

	i = 0;
	while(dongles[i])
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
	int			stop;

	compiler = (t_compiler *)arg;
	stop = 0;
	while (stop == 0)
	{
		if (check_bornout(compiler->coders) || check_n_compiles(compiler->coders))
		{
			stop = 1;
			pthread_mutex_lock(&compiler->m_monitor);
			compiler->stop_flag = true;
			stop_simulation(compiler->dongles);
			pthread_mutex_lock(&compiler->m_monitor);
			break;
		}
		usleep(500);
	}
	return (NULL);
}
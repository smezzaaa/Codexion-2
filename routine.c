/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:36:31 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/08 11:32:40 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_dongle	*get_first_dongle(t_coder *coder)
{
	//if (coder->id % 2 != 0)
	//	return(coder->l_dongle);
	//return(coder->r_dongle);
	if (coder->l_dongle->id < coder->r_dongle->id)
		return (coder->l_dongle);
	return (coder->r_dongle);
}

static t_dongle	*get_second_dongle(t_coder *coder)
{
	//if (coder->id % 2 != 0)
	//	return(coder->r_dongle);
	//return(coder->l_dongle);
	if (coder->l_dongle->id < coder->r_dongle->id)
		return (coder->r_dongle);
	return (coder->l_dongle);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!is_stopped(coder->compiler))
	{
		if (coder->id % 2 != 0 && coder->compiles == 0)
			usleep(500);
		if (!take_dongles(coder,
				get_first_dongle(coder), get_second_dongle(coder)))
			return (NULL);
		//if (!take_dongles(coder,
		//		get_second_dongle(coder), coder->compiler->d_cooldown))
		//	return (NULL);
		compiling(coder, coder->compiler->t_compile);
		release_dongle(coder, coder->compiler->start);
		if (is_stopped(coder->compiler))
			break ;
		debugging(coder, coder->compiler->t_debug);
		if (is_stopped(coder->compiler))
			break ;
		refactoring(coder, coder->compiler->t_refactor);
		if (coder->compiles == coder->compiler->n_compiles)
			break ;
	}
	return (NULL);
}

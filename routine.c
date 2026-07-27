/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:36:31 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/27 21:17:41 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!coder->compiler->stop_flag)
	{
		take_dongles(coder, coder->l_dongle);
		printf("%ld %d ha taken a dongle", gettime(), coder->id);
		take_dongles(coder, coder->r_dongle);
		printf("%ld %d ha taken a dongle", gettime(), coder->id);
		usleep(500);
	}
	return (NULL);
}

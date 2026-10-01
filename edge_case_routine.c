/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_case_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:01:02 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/01 11:47:43 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*one_coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!coder->compiler->burnout_flag)
	{
		pthread_cond_wait(&coder->compiler->dongles[0]->d_cond,
			&coder->compiler->dongles[0]->d_mutex);
	}
	return (NULL);
}

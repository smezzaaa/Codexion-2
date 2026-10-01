/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:12:46 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/01 12:01:04 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	create_threads(t_coder **coders, int n_coders)
{
	int	i;

	i = 0;
	if (n_coders == 1)
	{
		if (pthread_create(
				&coders[i]->t, NULL, one_coder_routine, coders[i]) != 0)
			return (false);
		return (true);
	}
	while (i < n_coders)
	{
		if (pthread_create(&coders[i]->t, NULL, coder_routine, coders[i]) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < n_coders)
	{
		if (pthread_join(coders[i]->t, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

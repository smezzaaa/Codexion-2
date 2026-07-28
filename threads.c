/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:12:46 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/28 18:10:12 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	create_threads(t_coder **coders, int n_coders)
{
	int	i;

	i = 0;
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

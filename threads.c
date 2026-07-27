/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 11:12:46 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/27 21:12:15 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_threads(t_coder **coders, int n_coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		if (pthread_create(&coders[i]->t, NULL, coder_routine, coders[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < n_coders)
	{
		if (pthread_join(coders[i]->t, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 17:58:02 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/20 17:35:38 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	parser(char **av)
{
	if (!av || !av[1] || !av[2] || !av[3] || !av[4]
		|| !av[5] || !av[6] || !av[7] || !av[8])
        return (false);
	if (atoi(av[1]) == 0)
		return (false);
	if (atoi(av[2]) == 0)
		return (false);
	if (atoi(av[3]) == 0)
		return (false);
	if (atoi(av[4]) == 0)
		return (false);
	if (atoi(av[5]) == 0)
		return (false);
	if (atoi(av[6]) == 0)
		return (false);
	if (atoi(av[7]) == 0)
		return (false);
	if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
		return (false);
	return (true);
}
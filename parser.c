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

int	parser(char **av)
{
	if (atoi(av[1]) == 0)
		return 0;
	if (atoi(av[2]) == 0)
		return 0;
	if (atoi(av[3]) == 0)
		return 0;
	if (atoi(av[4]) == 0)
		return 0;
	if (atoi(av[5]) == 0)
		return 0;
	if (atoi(av[6]) == 0)
		return 0;
	if (atoi(av[7]) == 0)
		return 0;
	if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
		return 0;
	return (1);
}
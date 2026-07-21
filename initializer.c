/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 10:38:55 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/20 10:38:55 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	assign_dongle(int n_coders, t_coder **coders, t_dongle **dongles)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		coders[i]->l_dongle = dongles[i];
		if (coders[i]->id == n_coders)
			coders[i]->r_dongle = dongles[0];
		else
			coders[i]->r_dongle = dongles[i + 1];
		i++;
	}
}

int    dongle_initializer(int n_coders, t_dongle **dongles)
{
    int i;

    i = 0;
    while (i < n_coders)
    {
		dongles[i] = (t_dongle *)malloc(sizeof(t_dongle));
		if (!dongles[i])
			return (1);
		dongles[i] = (t_dongle *)memset(dongles[i], 0, sizeof(t_dongle));
		dongles[i]->available = 0;
        dongles[i]->last_release = 0;
        pthread_mutex_init(&dongles[i]->d_mutex, NULL);
        pthread_cond_init(&dongles[i]->d_cond, NULL);
		dongles[i]->pq = (t_heap *)malloc(sizeof(t_heap));
		if (!dongles[i]->pq)
			return (1);
		if (create_pq(dongles[i]->pq) == 1)
			return (1);
        i++;
    }
	return (0);
}

int    coder_initializer(int n_coders, t_coder **coders, t_compiler *compiler)
{
    int i;

    i = 0;
    while (i < n_coders)
    {
		coders[i] = (t_coder *)malloc(sizeof(t_coder));
		coders[i] = (t_coder *)memset(coders[i], 0, sizeof(t_coder));
		if (!coders[i])
			return (1);
		coders[i]->id = i + 1;
        coders[i]->last_compile = 0;
        coders[i]->compiler = compiler;
        i++;
    }
    assign_dongle(n_coders, coders, compiler->dongles);
	return (0);
}

int	compiler_initializer(t_compiler *compiler, char **av)
{
    compiler->n_coders = atoi(av[1]);
    compiler->t_compile = atoi(av[2]);
    compiler->t_burnout = atoi(av[3]);
    compiler->t_debug = atoi(av[4]);
    compiler->t_refactor = atoi(av[5]);
    compiler->n_compiles = atoi(av[6]);
    compiler->d_cooldown = atoi(av[7]);
    compiler->scheduler = av[8];
    compiler->stop_flag = 0;
    compiler->dongles = (t_dongle **)malloc(sizeof(t_dongle *) * (size_t)(compiler->n_coders + 1));
	if (!compiler->dongles)
		return (1);
	compiler->coders = (t_coder **)malloc(sizeof(t_coder *) * (size_t)(compiler->n_coders + 1));
	if (!compiler->coders)
		return (1);
	compiler->dongles = (t_dongle **)memset(compiler->dongles, 0, (sizeof(t_dongle *) * (size_t)(compiler->n_coders + 1)));
    compiler->coders = (t_coder **)memset(compiler->coders, 0, (sizeof(t_coder *) * (size_t)(compiler->n_coders + 1)));
    if (dongle_initializer(compiler->n_coders, compiler->dongles) == 1)
		return (1);
	if (coder_initializer(compiler->n_coders, compiler->coders, compiler) == 1)
		return (1);
	fill_pq(compiler->n_coders, compiler->coders);
	return(0);
}

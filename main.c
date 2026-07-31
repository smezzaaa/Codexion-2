/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 14:31:13 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/31 14:50:17 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **av)
{
	if (parser(av) == 0 && ac <= 9)
		exit(1);
	t_compiler	compiler;
	int			i;

	i = 0;
	if (compiler_initializer(&compiler, av) == 1)
		ft_cleanup(compiler.n_coders, &compiler);
	compiler.start = gettime(0);
	if (pthread_create(&compiler.t_monitor, NULL, monitor, &compiler) != 0)
	{
		pthread_join(compiler.t_monitor, NULL);
		pthread_mutex_destroy(&compiler.m_monitor);
		pthread_cond_destroy(&compiler.c_monitor);
		ft_cleanup(compiler.n_coders, &compiler);
	}
	if (!create_threads(compiler.coders, compiler.n_coders))
	{
		pthread_join(compiler.t_monitor, NULL);
		pthread_mutex_destroy(&compiler.m_monitor);
		pthread_cond_destroy(&compiler.c_monitor);
		ft_cleanup(compiler.n_coders, &compiler);
	}
	pthread_join(compiler.t_monitor, NULL);
	ft_cleanup(compiler.n_coders, &compiler);
	pthread_mutex_destroy(&compiler.m_monitor);
	pthread_cond_destroy(&compiler.c_monitor);
}

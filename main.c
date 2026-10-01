/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 14:31:13 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/10/01 11:56:15 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_compiler	compiler;

	if (ac != 9 || !parser(av))
	{
		printf("[Warning] Input Error Detected.\n");
		exit(1);
	}
	if (!compiler_initializer(&compiler, av))
		ft_cleanup(compiler.n_coders, &compiler);
	compiler.start = gettime(0);
	if (pthread_create(&compiler.t_monitor, NULL, monitor, &compiler) != 0)
	{
		close_simulation(&compiler);
		ft_cleanup(compiler.n_coders, &compiler);
	}
	if (!create_threads(compiler.coders, compiler.n_coders))
	{
		close_simulation(&compiler);
		ft_cleanup(compiler.n_coders, &compiler);
	}
	close_simulation(&compiler);
	ft_cleanup(compiler.n_coders, &compiler);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 14:31:13 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/29 14:37:10 by smeza-ro         ###   ########.fr       */
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
	// compiler = (t_compiler){0};
	// compiler_initializer(av, &compiler);
	if (compiler_initializer(&compiler, av) == 1)
		ft_cleanup(compiler.n_coders, &compiler);
	compiler.start = gettime(0);
	//while (compiler.dongles[i])
	//{
	//	printf("first: %d, second: %d\n", compiler.dongles[i]->pq->arr[0]->id, compiler.dongles[i]->pq->arr[1]->id);
	//	i++;
	//}
	if (!create_threads(compiler.coders, compiler.n_coders))
		ft_cleanup(compiler.n_coders, &compiler);
	ft_cleanup(compiler.n_coders, &compiler);
}

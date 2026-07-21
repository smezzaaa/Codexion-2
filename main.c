/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 14:31:13 by smeza-ro          #+#    #+#             */
/*   Updated: 2026/07/21 19:34:10 by smeza-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int ac, char **av)
{
	if (parser(av) == 0 && ac <= 9)
		return 0;
	t_compiler compiler;
	// compiler = (t_compiler){0};
	// compiler_initializer(av, &compiler);
	if (compiler_initializer(&compiler, av) == 1)
	{
		ft_cleanup(compiler.n_coders, &compiler);
		return 0;
	}
	int i = 0;
	while (i < compiler.n_coders)
	{
		printf("first coder: %d\n", compiler.coders[i]->l_dongle->pq->arr[0]->id);
		printf("second coder: %d\n", compiler.coders[i]->l_dongle->pq->arr[1]->id);
		i++;
	}
	i = 0;
	tidy_pq(compiler.n_coders, compiler.coders);
	while (i < compiler.n_coders)
	{
		printf("new first coder: %d\n", compiler.coders[i]->l_dongle->pq->arr[0]->id);
		printf("new second coder: %d\n", compiler.coders[i]->l_dongle->pq->arr[1]->id);
		i++;
	}
	ft_cleanup(compiler.n_coders, &compiler);
}
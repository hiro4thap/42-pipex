/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:59:52 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 17:32:38 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (!is_args_greater_four(argc))
	{
		ft_printf("Pass no less than 4 arguments\n");
		return (1);
	}
	if (!is_args_greater_five(argc, argv))
	{
		ft_printf("Pass no less than 5 arguments including \"doc_here\"\n");
		return (1);
	}
	if (!ft_strncmp(argv[1], "here_doc", 9))
		pipex_hd(argv, envp, NULL, argc);
	else
		pipex(argv, envp, NULL, argc);
	return (0);
}

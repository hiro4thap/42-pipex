/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:03:39 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 17:41:32 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (!is_args_four(argc))
	{
		ft_printf("Pass no less than 4 arguments\n");
		return (1);
	}
	pipex(argv, envp);
	return (0);
}

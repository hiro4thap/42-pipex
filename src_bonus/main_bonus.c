/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:59:52 by hiono             #+#    #+#             */
/*   Updated: 2024/04/17 18:19:04 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (!is_args_greater_four(argc))
	{
		ft_printf("give 4 parameters\n");
		return (1);
	}
	pipex(argv, envp);
	return (0);
}

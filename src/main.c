/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:03:39 by hiono             #+#    #+#             */
/*   Updated: 2024/04/15 17:38:40 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	f_in;
	int	f_out;

	if (!is_valid_args(argc, argv))
		return (1);
	f_in = open(argv[1], O_RDONLY);
	f_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC); //TODO:know options
	if (f_in < 0 || f_out < 0)
	{
		ft_printf("Fail to open file\n");
		return (1);
	}
	pipex(f_in, f_out, argv, envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:03:39 by hiono             #+#    #+#             */
/*   Updated: 2024/04/16 16:03:42 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	f_in;
	int	f_out;

	if (!is_valid_args(argc, argv))
	{
		write(2, "file error\n", 11);
		return (1);
	}
	f_in = open(argv[1], O_RDONLY);
	f_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f_in < 0 || f_out < 0)
	{
		write(2, "fail to open file\n", 18); 
		return (1);
	}
	pipex(f_in, f_out, argv, envp);
	return (0);
}

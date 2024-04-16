/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:06:00 by hiono             #+#    #+#             */
/*   Updated: 2024/04/16 17:50:12 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	is_args_four(int argc)
{
	if (argc != 5)
	{
		ft_printf("Please give 4 arguments to the program\n");
		return (0);
	}
	return (1);
}

int	is_valid_args(int argc, char **argv)
{
	(void) argv;
	if (!is_args_four(argc))
		return (0);
	if (access(argv[1], R_OK))
	{
		return (0);
	}
	//TODO:argv[2], argv[3] can include option.
	// needs to split and validate only first element.
	// other elements should be sent to args of commands.
	//if (access(ft_strjoin("/usr/bin/", argv[2]), X_OK))
	//{
	//	ft_printf("command \"%s\" does not exist\n", argv[2]);
	//	return (0);
	//}
	//if (access(ft_strjoin("/usr/bin/", argv[3]), X_OK))
	//{
	//	ft_printf("command \"%s\" does not exist\n", argv[3]);
	//	return (0);
	//}
	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
	{
		return (0);
	}
	return (1);
}

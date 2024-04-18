/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:00:21 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 15:54:15 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	is_args_greater_four(int argc)
{
	if (argc < 5)
	{
		return (0);
	}
	return (1);
}

int	is_args_greater_five(int argc, char **argv)
{
	if (argc < 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		return (0);
	}
	return (1);
}

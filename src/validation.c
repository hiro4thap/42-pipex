/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:06:00 by hiono             #+#    #+#             */
/*   Updated: 2024/04/17 15:02:49 by hiono            ###   ########.fr       */
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

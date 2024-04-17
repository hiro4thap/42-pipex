/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:00:21 by hiono             #+#    #+#             */
/*   Updated: 2024/04/17 18:09:17 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	is_args_greater_four(int argc)
{
	if (argc < 5)
	{
		ft_printf("Please give no less than 4 arguments to the program\n");
		return (0);
	}
	return (1);
}

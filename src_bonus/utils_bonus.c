/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:00:11 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 18:33:18 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	exit_pipeerr(void)
{
	perror("Pipe error\n");
	exit(EXIT_FAILURE);
}

void	exit_forkerr(void)
{
	perror("Fork error\n");
	exit(EXIT_FAILURE);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	printerr(char *msg, char *fail)
{
	while (*msg)
	{
		while (*msg && *msg != '%')
		{
			write(2, msg, 1);
			msg++;
		}
		if (*msg && !ft_strncmp(msg, "%s", 2))
		{
			write(2, fail, ft_strlen(fail));
			msg++;
			msg++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:01:05 by hiono             #+#    #+#             */
/*   Updated: 2024/04/17 18:01:16 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define EXIT_COMMAND_NOT_FOUND 127

char	**get_evnp_path(char **envp);
char	*ft_strdirjoin(char	*s1, char *s2);
char	**split_cmd(char *cmd);
int		is_args_four(int argc);
void	pipex(char **argv, char **envp);
void	printerr(char *msg, char *fail);
void	free_strs(char **strs);

#endif

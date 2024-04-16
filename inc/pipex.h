/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:43:35 by hiono             #+#    #+#             */
/*   Updated: 2024/04/16 18:56:31 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

char	**get_evnp_path(char **envp);
char	*ft_strdirjoin(char	*s1, char *s2);
char	**split_cmd(char *cmd);
int		is_valid_args(int argc, char **argv);
void	pipex(int fi, int fo, char **argv, char **envp);

#endif

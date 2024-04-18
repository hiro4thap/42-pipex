/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:01:05 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 18:37:17 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define EXIT_COMMAND_NOT_FOUND 127

char	**get_evnp_path(char **envp);
char	*ft_strdirjoin(char	*s1, char *s2);
char	**split_cmd(char *cmd);
int		is_args_greater_four(int argc);
int		is_args_greater_five(int argc, char **argv);
void	pipex(char **argv, char **envp, int pipefd_p[2], int argc);
void	pipex_hd(char **argv, char **envp, int pipefd_p[2], int argc);
void	printerr(char *msg, char *fail);
void	free_strs(char **strs);
void	exit_pipeerr(void);
void	exit_forkerr(void);

size_t	gnl_ft_strlen(const char *str);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
char	*gnl_ft_strjoin(char *s1, char const *s2);
char	*gnl_ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif

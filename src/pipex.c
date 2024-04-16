/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:07:38 by hiono             #+#    #+#             */
/*   Updated: 2024/04/16 19:48:02 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_exe_com1(int fi, int pipefd[2], char **argv, char **envp)
{
	char	**args;
	char	*cmd;
	char	**dirs;

	close(pipefd[0]);
	args = split_cmd(argv[2]);
	dup2(fi, STDIN_FILENO);
	close(fi);
	dup2(pipefd[1], STDOUT_FILENO);
	dirs = get_evnp_path(envp);
	while (*dirs)
	{
		cmd = ft_strdirjoin(*dirs, args[0]);
		execve(cmd, args, envp);
		free(cmd);
		dirs++;
	}
	close(pipefd[1]);
	free(args);
	exit(127); //TODO:needs to be set in header
}

void	parent_exe_com2(int fo, int pipefd[2], char **argv, char **envp)
{
	char	**args;
	char	*cmd;
	char	**dirs;

	close(pipefd[1]);
	args = split_cmd(argv[3]);
	dup2(fo, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	dirs = get_evnp_path(envp);
	while (*dirs)
	{
		cmd = ft_strdirjoin(*dirs, args[0]);
		execve(cmd, args, envp);
		free(cmd);
		dirs++;
	}
	close(pipefd[0]);
	close(fo);
	free(args); //TODO:free every elements as well
	exit(127); //TODO:needs to be set in header
}

void	pipex(int fi, int fo, char **argv, char **envp)
{
	(void) fi;
	(void) fo;
	(void) argv;
	(void) envp;

	int	pipefd[2];
	int	pid;
	
	if (pipe(pipefd) == -1)
	{
		ft_printf("Pipe error\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Fork error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_exe_com1(fi, pipefd, argv, envp);
	else if (0 < pid)
		parent_exe_com2(fo, pipefd, argv, envp);
}

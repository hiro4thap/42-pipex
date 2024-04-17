/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:07:38 by hiono             #+#    #+#             */
/*   Updated: 2024/04/17 18:16:22 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_dup_fds(int pipefd[2], char **argv)
{
	int		fi;

	if (access(argv[1], F_OK))
	{
		printerr("no such file or directory: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	else if (access(argv[1], R_OK))
	{
		printerr("permission denied: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	fi = open(argv[1], O_RDONLY);
	if (fi < 0)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	dup2(fi, STDIN_FILENO);
	close(fi);
	dup2(pipefd[1], STDOUT_FILENO);
}

void	child_exe_cmd(int pipefd[2], char **argv, char **envp)
{
	char	**args;
	char	**dirs;
	int		i;
	char	*cmd;

	args = split_cmd(argv[2]);
	dirs = get_evnp_path(envp);
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strdirjoin(dirs[i], args[0]);
		execve(cmd, args, envp);
		free(cmd);
		i++;
	}
	close(pipefd[1]);
	printerr("command not found: %s\n", args[0]);
	free_strs(args);
	free_strs(dirs);
	exit(EXIT_COMMAND_NOT_FOUND);
}

void	parent_dup_fds(int pipefd[2], char **argv)
{
	int		fo;

	if (!access(argv[4], F_OK) && access(argv[4], W_OK))
	{
		printerr("permission denied: %s\n", argv[4]);
		exit(EXIT_FAILURE);
	}
	fo = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fo < 0)
		exit(EXIT_FAILURE);
	close(pipefd[1]);
	dup2(fo, STDOUT_FILENO);
	close(fo);
	dup2(pipefd[0], STDIN_FILENO);
}

void	parent_exe_cmd(int pipefd[2], char **argv, char **envp)
{
	char	**args;
	char	**dirs;
	int		i;
	char	*cmd;

	args = split_cmd(argv[3]);
	dirs = get_evnp_path(envp);
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strdirjoin(dirs[i], args[0]);
		execve(cmd, args, envp);
		free(cmd);
		i++;
	}
	close(pipefd[0]);
	printerr("command not found: %s\n", args[0]);
	free_strs(args);
	free_strs(dirs);
	exit(EXIT_COMMAND_NOT_FOUND);
}

void	pipex(char **argv, char **envp)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe error\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		child_dup_fds(pipefd, argv);
		child_exe_cmd(pipefd, argv, envp);
	}
	else if (0 < pid)
	{
		parent_dup_fds(pipefd, argv);
		parent_exe_cmd(pipefd, argv, envp);
	}
}

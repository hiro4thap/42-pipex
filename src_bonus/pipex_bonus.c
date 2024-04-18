/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:00:01 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 15:16:47 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	child_dup_fds(int pipefd[2], char *in)
{
	int		fi;

	if (access(in, F_OK))
	{
		printerr("no such file or directory: %s\n", in);
		exit(EXIT_FAILURE);
	}
	else if (access(in, R_OK))
	{
		printerr("permission denied: %s\n", in);
		exit(EXIT_FAILURE);
	}
	fi = open(in, O_RDONLY);
	if (fi < 0)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	dup2(fi, STDIN_FILENO);
	close(fi);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	child_exe_cmd(char **argv, char **envp)
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
	printerr("command not found: %s\n", args[0]);
	free_strs(args);
	free_strs(dirs);
	exit(EXIT_COMMAND_NOT_FOUND);
}

void	parent_dup_fds(int pipefd_p[2], int pipefd_c[2], char *out)
{
	int		fo;

	if (out && !access(out, F_OK) && access(out, W_OK))
	{
		printerr("permission denied: %s\n", out);
		exit(EXIT_FAILURE);
	}
	close(pipefd_c[1]);
	if (out)
	{
		fo = open(out, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fo < 0)
			exit(EXIT_FAILURE);
		dup2(fo, STDOUT_FILENO);
		close(fo);
	}
	else
	{
		dup2(pipefd_p[1], STDOUT_FILENO);
		close(pipefd_p[1]);
	}
	dup2(pipefd_c[0], STDIN_FILENO);
	close(pipefd_c[0]);
}

void	parent_exe_cmd(char *cmds, char **envp)
{
	char	**args;
	char	**dirs;
	int		i;
	char	*cmd;

	args = split_cmd(cmds);
	dirs = get_evnp_path(envp);
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strdirjoin(dirs[i], args[0]);
		execve(cmd, args, envp);
		free(cmd);
		i++;
	}
	printerr("command not found: %s\n", args[0]);
	free_strs(args);
	free_strs(dirs);
	exit(EXIT_COMMAND_NOT_FOUND);
}

void	pipex(char **argv, char **envp, int pipefd_p[2], int argc)
{
	int	pipefd_c[2];
	int	pid;

	if (pipe(pipefd_c) == -1)
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
	// child
	//  has child -> call pipex wich pipex called now
	//  else -> child_dup_fds
	if (pid == 0 && argc > 5)
		pipex(argv, envp, pipefd_c, --argc);
	else if (pid == 0 && argc == 5)
	{
		child_dup_fds(pipefd_c, argv[1]);
		child_exe_cmd(argv, envp);
	}
	// parent
	//  has parent -> fdout: p1 in arg / fdin: p0 in current vars
	//  else -> fdout: outfile / fdin: p0 in current vars
	else if (0 < pid)
	{
		if (!pipefd_p)
			parent_dup_fds(pipefd_p, pipefd_c, argv[argc - 1]);
		else
			parent_dup_fds(pipefd_p, pipefd_c, NULL);
		parent_exe_cmd(argv[argc - 2], envp);
	}
}

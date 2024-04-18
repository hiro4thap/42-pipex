/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_hd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:31:51 by hiono             #+#    #+#             */
/*   Updated: 2024/04/18 18:35:15 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	child_dup_fds_hd(int pipefd[2], char *limiter)
{
	int		limlen;
	char	*line;
	char	*input;

	input = NULL;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		limlen = ft_strlen(limiter);
		if (!ft_strncmp(line, limiter, limlen) && line[limlen] == '\n')
			break ;
		if (!input)
			input = ft_strdup(line);
		else
			input = ft_strjoin(input, line);
		free(line);
	}
	free(line);
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
}

void	parent_dup_fds_hd(int pipefd_p[2], int pipefd_c[2], char *out)
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
		fo = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
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

void	parent_exe_cmd_hd(char *cmds, char **envp)
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

void	pipex_hd(char **argv, char **envp, int pipefd_p[2], int argc)
{
	int	pipefd_c[2];
	int	pid;

	if (pipe(pipefd_c) == -1)
		exit_pipeerr();
	pid = fork();
	if (pid == -1)
		exit_forkerr();
	if (pid == 0 && argc > 5)
		pipex_hd(argv, envp, pipefd_c, --argc);
	else if (pid == 0 && argc == 5)
		child_dup_fds_hd(pipefd_c, argv[2]);
	else if (0 < pid)
	{
		if (!pipefd_p)
			parent_dup_fds_hd(pipefd_p, pipefd_c, argv[argc - 1]);
		else
			parent_dup_fds_hd(pipefd_p, pipefd_c, NULL);
		parent_exe_cmd_hd(argv[argc - 2], envp);
	}
}

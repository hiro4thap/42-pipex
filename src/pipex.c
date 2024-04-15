/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:07:38 by hiono             #+#    #+#             */
/*   Updated: 2024/04/15 18:09:08 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_exe_com1(int fi, int pipefd[2], char **argv, char **envp)
{
	char **args;

	close(pipefd[0]);
	args = ft_split(argv[2], ' ');
	dup2(fi, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	execve("/usr/bin/grep", args, envp); //TODO:1st arg should be flex
	close(pipefd[1]);
	close(fi);
	free(args);
	exit(10); //TODO:needs to be set in header
}

void	parent_exe_com2(int fo, int pipefd[2], char **argv, char **envp)
{
	char **args;

	close(pipefd[1]);
	args = ft_split(argv[3], ' ');
	dup2(fo, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	execve("/usr/bin/wc", args, envp);
	close(pipefd[0]);
	close(fo);
	free(args);
	exit(20);
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
	// Parent
	// 	close fd-w, fi
	//	wait....
	//
	// Child
	// 	close fd-r, fo
	// 	dup(stdin -> fi)
	// 	dup(stdout -> fd-w)
	// 	execve(argv[2]) => write(fd-w, result, len)
	// 	close fd-w, fi
	// 	exit
	//
	// Parent
	//  validate exit_code of child
	//   if false -> exit;
	//  dup(stdin -> fd-r)
	//  dup(stdout -> fo)
	//  execve(argv[3])
	//  close rd-r, fo
	//  exit
}

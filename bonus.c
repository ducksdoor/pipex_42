/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:57:38 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/16 23:57:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_extra(int *fd, int pid2, char **argv, char **envp)
{
	int	fd_dest;
	int	x;

	x = 0;
	while (argv)
	{
		x++;
	}
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = open(argv[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_dest == -1)
		{
			perror("open");
			exit(errno);
		}
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(argv[x - 1], envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_middle_c(int *fd, int pidx, char *argv, char **envp)
{
	if (pidx < 0)
		return ;
	if (pidx == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_exe(argv, envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_wait(int *pid, int x)
{
	int	y;

	y = 0;
	while (y < x)
	{
		waitpid(pid[x], NULL, 0);
		y++;
	}
	exit(1);
}

static void	ft_process(int narg, char **argv, char **envp)
{
	int	fd[2];
	int	pid[100];
	int	x;

	if (pipe(fd) == -1)
		exit (1);
	x = 1;
	pid[x] = fork();
	ft_first_children(fd, pid[x], argv, envp);
	while (x < narg)
	{
		x++;
		pid[x] = fork();
		ft_middle_c(fd, pid[x], argv[x + 1], envp);
	}
	pid[x] = fork();
	ft_extra(fd, pid[x], argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	ft_wait(pid, x);
}

void	ft_big_pipex(int argc, char **argv, char **envp)
{
	int	x;

	x = argc - 3;
	ft_process(x, argv, envp);
	exit(1);
}

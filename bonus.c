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

static void	ft_last_children(int fd[2], int argc, char **argv, char **envp)
{
	int		fd_dest;
	pid_t	pidf;

	pidf = fork();
	if (pidf < 0)
		return ;
	if (pidf == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = ft_open(argv[argc - 1], 2);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(argv[argc - 2], envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_middle_c(int fdp[2], int fd[2], char *argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	if (pid == 0)
	{
		close(fd[READ_END]);
		dup2(fdp[READ_END], STDIN_FILENO);
		dup2(fdp[1], STDOUT_FILENO);
		close(fd[1]);
		ft_exe(argv, envp);
		perror("exe");
		exit(errno);
	}
	else
	{
		close(fdp[READ_END]);
		close(fd[WRITE_END]);
	}
	return ;
}

static void	ft_process(int fdp[2], int argc, char **argv, char **envp)
{
	int	i;
	int	x;
	int	fd[2];

	i = 3;
	x = 0;
	while (x < (argc - 5))
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(errno);
		}
		ft_middle_c(fdp, fd, argv[i], envp);
		i++;
		x++;
	}
	ft_last_children(fd, argc, argv, envp);
}

void	ft_big_pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe:");
		exit(errno);
	}
	pid = fork();
	ft_first_children(fd, pid, argv, envp);
	close(fd[WRITE_END]);
	ft_process(fd, argc, argv, envp);
	close(fd[READ_END]);
}

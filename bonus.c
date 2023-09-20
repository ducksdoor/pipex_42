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

static void	ft_last_children(int *fd, char *cmd, char *file, char **envp)
{
	int		fd_dest;
	pid_t	pidf;

	pidf = fork();
	if (pidf < 0)
		return ;
	if (pidf == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = ft_open(file, 2);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(cmd, envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_middle_c( int fd[2], char *argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_exe(argv, envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_process(int argc, char **argv, char **envp)
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
		ft_middle_c(fd, argv[i], envp);
		i++;
		x++;
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
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
	ft_process(argc, argv, envp);
	ft_last_children(fd, argv[argc - 2], argv[argc -1], envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	//while (1);
}



/* static void	ft_process(int narg, char **argv, char **envp)
{
	int	pid[100];
	int	x;

	x = 1;
	pid[x] = fork();
	ft_first_children(fd, pid[x], &argv[2], envp);
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
	exit(1);
} */
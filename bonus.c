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

static void	ft_last_children(int *fd, int pid2, char **argv, char **envp)
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
		dup2(fd[READ_END], STDOUT_FILENO);
		close(fd[READ_END]);
		fd_dest = ft_open(argv[x], 2);
		x--;
		dup2(fd_dest, STDIN_FILENO);
		close(fd_dest);
		ft_exe(argv[x], envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_middle_c(int *fd, int ofd, char *argv, char **envp) //(( revisar ofd))
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
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

static void	ft_process(int fnp[2], int argc, char **argv, char **envp)
{
	int		i;
	int		x;
	int		fd[2];
/* 
	int file1 = open(file);
	close file1;
	file1 = open(patata); */
	i = 3;
	x = 0;
	while (x <= (argc - 5))
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(errno);
		}
//		if -- primer midle
		 /*crear aux// crear pid dentro*/ft_middle_c(&fnp[1], fd[0], argv[i], envp);
//		else if -- siguientes ft_middle_c(aux, fd[0], argv[i], envp);
//										cerrar aux.
		i++;
		x++;
	}
	close(fd[READ_END]);
	close(fd[WRITE_END]);
}




void	ft_big_pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe:");
		exit(errno);
	}
	pid = fork();
	ft_first_children(fd, pid, argv, envp);
	/*devuelve fd*/ft_process(fd, argc, argv, envp);
	pid2 = fork();
	ft_last_children(fd, pid2, &argv[argc - 1], envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	//leer mas sobre los wait!
	exit(1);
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
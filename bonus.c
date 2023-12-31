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
		ft_error("fork");
	if (pidf == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = ft_open(argv[argc - 1], 2);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(argv[argc - 2], envp);
		ft_error("exe");
	}
	else
		waitpid(pidf, NULL, 0);
}

static void	ft_middle_c(int fdp[2], int fd[2], char *argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		close(fd[READ_END]);
		dup2(fdp[READ_END], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_exe(argv, envp);
		ft_error("exe");
	}
	close(fdp[READ_END]);
	close(fd[WRITE_END]);
}

static void	ft_process(int fdp[2], int argc, char **argv, char **envp)
{
	int	i;
	int	x;
	int	fd[2];
	int	aux[2];

	i = 3;
	x = 0;
	while (x < (argc - 5))
	{
		if (pipe(fd) == -1)
			ft_error("pipe");
		if (i == 3)
			ft_middle_c(fdp, fd, argv[i], envp);
		if (i > 3)
			ft_middle_c(aux, fd, argv[i], envp);
		aux[0] = fd[0];
		aux[1] = fd[1];
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
		ft_error("pipe:");
	pid = fork();
	ft_first_children(fd, pid, argv, envp);
	close(fd[WRITE_END]);
	ft_process(fd, argc, argv, envp);
	close(fd[READ_END]);
}

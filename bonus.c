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

static void ft_middle_c(int *fd, int pidx, char **argv, char **envp, int x) 
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
		ft_exe(argv[x], envp);
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

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid[argc - 3];
	int	x;
/* 
	if (argc == 5)
	{
		ft_printf("Necesito más argumentos");
		exit(1);
	} */
	if (pipe(fd) == -1)
		return (1);
	x = 0;
	pid[x] = fork();
	ft_first_children(fd, pid[x], argv, envp);
	while (x < argc - 3)
	{
		x++;
		pid[x] = fork();
		ft_middle_c(fd, pid[x], argv, envp, (x + 2));
	}
	pid[x] = fork();
	ft_second_children(fd, pid[x], argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	ft_wait(pid, x);
}

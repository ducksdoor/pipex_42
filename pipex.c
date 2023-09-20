/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:24:43 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/16 21:31:33 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	ft_pipex(char **argv, char **envp)
{
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(errno);
	}
	pid1 = fork();
	ft_first_children(fd, pid1, argv, envp);
	pid2 = fork();
	ft_second_children(fd, pid2, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}


int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_printf("Necesito mas argumentos");
		exit(1);
	}
	if (argc == 5)
		ft_pipex(argv, envp);
	else
		ft_big_pipex(argc, argv, envp);
}

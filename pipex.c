/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:24:43 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/02 16:24:51 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int pid2;

	if (argc != 5)
	{
		ft_printf("mas argumentos!");
		exit(1);
	}
	if (pipe(fd) == -1)
		return 1;
	pid1 = fork();
	ft_first_children(fd, pid1, argv, envp);
	close(fd[WRITE_END]);
	pid2 = fork();
	ft_second_children(fd, pid2, argv);
	close(fd[READ_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 42;
}

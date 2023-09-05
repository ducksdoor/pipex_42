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

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid1;
	int pid2;

	if (argc != 5)
	{
		ft_printf("mas argumentos!");
		exit(1);
	}
/* 	pipe(fd);
	printf("PRIMERA VEZ QUE SE EJECUTA PIPE:%i\n%i", fd[0], fd[1]); */
	if (pipe(fd) == -1)
		return 1;
	printf("PRIMERA VEZ QUE SE EJECUTA PIPE:%i\n%i", fd[0], fd[1]);
	pid1 = fork();
	ft_first_children(fd, pid1, argv[2], argv[3]);
	close(fd[WRITE_END]);
	pid2 = fork();
	ft_second_children(fd, pid2, argv[4], argv[5]);
/* 	close(fd[0]);*/
	//ft_printf("este es el proceso padre(pid1 > 0). El proceso espera al hijo\n");
/* 	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0); */
	return 0;
}

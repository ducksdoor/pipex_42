/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:14:49 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/06 21:14:58 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_first_children(int *fd, int pid1, char **argv, char **envp)
{
	int		texto;

	if (pid1 < 0)
	{
		perror("fork:");
		exit(errno);
	}
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		texto = open(argv[1], O_RDONLY);
		if (texto == -1)
		{
			perror("open");
			exit(errno);
		}
		dup2(texto, STDIN_FILENO);
		close(texto);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_exe(argv[2], envp);
		perror("exe");
		exit(errno);
	}
}

void	ft_second_children(int *fd, int pid2, char **argv, char **envp)
{
	int	fd_dest;

	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(argv[3], envp);
		perror("exe");
		exit(errno);
	}
}

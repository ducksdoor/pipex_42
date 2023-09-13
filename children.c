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
	char	*text_file;

	printf("%s\n", argv[2]);
	texto = open(argv[1], O_RDONLY);
	if (texto == -1)
	{
		perror("open");
		exit(1);
	}
	text_file = ft_get_next_line(texto);
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		ft_printf("el miedo mata a la mente\n");
		dup2(fd[WRITE_END], STDOUT_FILENO);
		//ft_printf("Esto es patata?\n");
		ft_exe(argv[2], envp);
		close(fd[WRITE_END]);
	}
}
/* 		perror("execlp");
		exit(EXIT_FAILURE); */

void	ft_second_children(int *fd, int pid2, char **argv)
{
	int	fd_dest;
	char	*buf;
	ssize_t	bytesRead;
	ssize_t	bytesWritten;
	
/* 	if (buf == NULL)
	{
		perror("malloc");
		exit(1);
	} */
	if (!argv[4] || !argv[3])
		//exit(1);
		;
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		fd_dest = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_dest, STDOUT_FILENO);
		bytesRead = read(fd[READ_END], &buf, sizeof(buf));
		while (bytesRead > 0)
		{
			bytesWritten = write(fd_dest, &buf, bytesRead);
			if (bytesWritten == -1)
			{
				perror("write");
				exit(1);
			}
			bytesRead = read(fd[READ_END], &buf, sizeof(buf));
		}
/* 		read(fd[READ_END], &buf, ft_strlen(buf));
		write(fd_dest, &buf, ft_strlen(buf));
		printf("esto es buf:%s\n", buf); */
		close(fd[READ_END]);
	}
}

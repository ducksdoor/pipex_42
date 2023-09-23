/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonustwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:34:25 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/22 23:34:28 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_secondhere_children(int *fd, int pid2, char **argv, char **envp)
{
	int	fd_dest;

	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = ft_open(argv[5], 2);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		ft_exe(argv[4], envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_firsthere_children(int *fd, int pid1, char **argv, char **envp)
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
		texto = ft_open(".here_doc", 1);
		dup2(texto, STDIN_FILENO);
		close(texto);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		ft_exe(argv[3], envp);
		perror("exe");
		exit(errno);
	}
}

static void	ft_simple_pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(errno);
	}
	pid1 = fork();
	ft_firsthere_children(fd, pid1, argv, envp);
	pid2 = fork();
	ft_secondhere_children(fd, pid2, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	ft_here_pipex(int argc, char **argv, char **envp)
{
	char	*x;
	int		bool;
	int		fd;
	char	*line;

	if (argc != 6)
	{
		ft_printf("Necesito mas argumentos");
		exit(1);
	}
	bool = 1;
	x = argv[1];
	fd = ft_open(".here_doc", 2);
	while (bool == 1)
	{
		line = ft_get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) - 1) == 0)
			bool = 0;
		if (bool == 1)
			write(fd, line, ft_strlen(line));
	}
	ft_simple_pipex(argv, envp);
}

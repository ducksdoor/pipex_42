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
		if (ft_strncmp("here_doc", argv[1], 8) != 0)
			fd_dest = ft_open(argv[4], 2);
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
			fd_dest = ft_open(argv[5], 2);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		if (ft_strncmp("here_doc", argv[1], 8) != 0)
			ft_exe(argv[3], envp);
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
			ft_exe(argv[4], envp);
		ft_error("exe");
	}
}

void	ft_first_children(int *fd, int pid1, char **argv, char **envp)
{
	int		texto;

	if (pid1 < 0)
		ft_error("fork:");
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		if (ft_strncmp("here_doc", argv[1], 8) != 0)
			texto = ft_open(argv[1], 1);
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
			texto = ft_open(".here_doc", 3);
		dup2(texto, STDIN_FILENO);
		close(texto);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (ft_strncmp("here_doc", argv[1], 8) != 0)
			ft_exe(argv[2], envp);
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
			ft_exe(argv[3], envp);
		ft_error("exe");
	}
}

void	ft_pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("pipe");
	pid1 = fork();
	ft_first_children(fd, pid1, argv, envp);
	pid2 = fork();
	ft_second_children(fd, pid2, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit(1);
}

void	leaks(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char **argv, char **envp)
{
	int		bool;
	int		fd;
	char	*line;

	atexit(leaks);
	if (argc < 5)
		ft_error("Mas argumentos");
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		if (argc < 6)
			ft_error("Argumentos para heredoc");
		bool = 1;
		fd = ft_open(".here_doc", 2);
		while (bool == 1)
		{
			line = ft_get_next_line(0);
			bool = protect_loop(fd, line, argv[2]);
			free(line);
		}
		ft_pipex(argv, envp);
	}
	if (argc == 5)
		ft_pipex(argv, envp);
	ft_big_pipex(argc, argv, envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rute.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:16:27 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/06 21:16:39 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_search2(char *object, char *command)
{
	char	**path;
	int		cont;
	char	*finish;

	path = ft_split(object + 5, ':');
	cont = 0;
	while (path[cont])
	{
		finish = ft_strjoin(path[cont], "/");
		finish = ft_strjoin(finish, command);
		if (access(finish, F_OK) == 0)
			return (finish);
		cont++;
	}
	perror("command:");
	exit(errno);
}

char	*ft_search(char **env)
{
	int		pos;
	char	*routes;

	pos = 0;
	while (env[pos])
	{
		routes = ft_strnstr(env[pos], "PATH=", 5);
		if (routes != NULL)
			return (routes);
		pos++;
	}
	perror("path:");
	exit(errno);
}

void	ft_exe(char *command, char **envp)
{
	char	*object;
	char	*finish;
	char	**cmd;

	object = ft_search(envp);
	cmd = ft_split(command, ' ');
	finish = ft_search2(object, cmd[0]);
	dprintf(2, "cmd: %s\n", finish);
	dprintf(2, "cmd: %s\n", cmd[0]);
	execve(finish, cmd, envp);
	perror(command);
	exit(errno);
}

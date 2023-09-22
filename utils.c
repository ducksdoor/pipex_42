/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:22:57 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/06 21:23:01 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_absolute(char **cmd)
{
	if (ft_strncmp("/", cmd[0], 1) == 0)
		return (1);
	if (ft_strncmp("./", cmd[0], 2) == 0)
		return (1);
	if (ft_strncmp("../", cmd[0], 3) == 0)
		return (1);
	return (0);
}

char	*ft_search2(char *object, char *command)
{
	char	**path;
	int		cont;
	char	*finish;

	path = ft_protsplit(object + 5, ':');
	cont = 0;
	while (path[cont])
	{
		finish = ft_protstrjoin(path[cont], "/");
		finish = ft_protstrjoin(finish, command);
		if (access(finish, F_OK) == 0)
			return (finish);
		cont++;
	}
	perror("error command ");
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
	return (NULL);
}

void	ft_exe(char *command, char **envp)
{
	char	*object;
	char	*finish;
	char	**cmd;

	object = NULL;
	cmd = ft_protsplit(command, ' ');
	if (ft_is_absolute(&cmd[0]))
		finish = cmd[0];
	else
	{
		if (envp == NULL)
			finish = ft_protstrjoin ("./", cmd[0]);
		else
			object = ft_search(envp);
			finish = ft_search2(object, cmd[0]);
		if (!finish)
		{
			perror("ruta comando");
			exit(errno);
		}
	}
	execve(finish, cmd, envp);
	perror(command);
	exit(errno);
}

int	ft_open(char *file, int x)
{
	int	texto;

	if (x == 1)
	{
		texto = open(file, O_RDONLY);
		if (texto == -1)
		{
			perror("open write");
			exit(errno);
		}
	}
	if (x == 2)
	{
		texto = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (texto == -1)
		{
			perror("open close");
			exit(errno);
		}
	}
	return (texto);
}

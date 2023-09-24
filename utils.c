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
	perror("error cmd");
	exit(errno);
}

char	*ft_search(char **env, char *cmd)
{
	int		pos;
	char	*routes;
	char	*finish;

	pos = 0;
	while (env[pos])
	{
		routes = ft_strnstr(env[pos], "PATH=", 5);
		if (routes != NULL)
		{
			finish = ft_search2(routes, cmd);
			return (finish);
		}
		pos++;
	}
	return (NULL);
}

void	ft_exe(char *command, char **envp)
{
	char	*finish;
	char	**cmd;

	finish = NULL;
	cmd = ft_protsplit(command, ' ');
	if (ft_is_absolute(&cmd[0]))
		finish = cmd[0];
	else
	{
		if (envp == NULL)
		{
			finish = ft_protstrjoin ("./", cmd[0]);
			if (access(finish, F_OK) != 0)
				ft_error(command);
		}
		else
			finish = ft_search(envp, cmd[0]);
		if (!finish)
			ft_error("ruta comando");
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
			ft_error("open write");
	}
	if (x == 2)
	{
		texto = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (texto == -1)
			ft_error("open close");
	}
	if (x == 3)
	{
		texto = open(file, O_CREAT | O_WRONLY |O_APPEND, 0644);
		if (texto == -1)
			ft_error("open close");
	}
	return (texto);
}

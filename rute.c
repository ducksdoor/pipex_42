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

//      el programa busca de aqui     //
//PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki


char	*ft_search2(char *object, char *command)
{
	char **path;
	int cont;
	char *finish;

	path = ft_split(object + 5, ':');
//	ft_printf("%s\n", path[0]);
	cont = 0;
	while (path)
	{
		finish = ft_strjoin(path[cont], "/");
		finish = ft_strjoin(finish, command);
		if (access(finish, F_OK) == 0)
		{
//			ft_printf("|%s|\n", finish);
			return (finish);
		}
		cont++;
	}
	return (NULL);
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
	int		x;
	char	*object;
	char	*finish;

	object = ft_search(envp);
//	ft_printf("%s\n", object);
	if (object == NULL)
		exit(1);
	finish = ft_search2(object, command);
	ft_printf("|%s|\n", finish);
	x = execve(finish, &command, envp);
	if (x == -1)
	{
		printf("esto no rula del todo\n");
		exit(1);
	}
	printf("encontraste la ruta\n");
}

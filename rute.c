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

void	ft_exe(char *command, char **envp)
{
	int	x;
	x = execve("/bin", &command, envp);
}


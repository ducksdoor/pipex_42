/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:17:33 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/18 22:17:37 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_bool(int i)
{
	if (i % 2 == 0)
		return (0);
	else if (i % 2 != 0)
		return (1);
	return (0);
}



/* void	ft_wait(int *pid, int x)
{
	int	y;

	y = 0;
	while (y < x)
	{
		waitpid(pid[x], NULL, 0);
		y++;
	}
	exit(1);
} */




/* int	created_pid(int x)
{
	int	pid;

	pid = fork();
	return (pid);
} */

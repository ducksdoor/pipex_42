/* ************************************************************************** */
/*                                                                             */
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

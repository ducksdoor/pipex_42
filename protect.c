/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:47:32 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/17 00:47:45 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_protsplit(char *str, char c)
{
	char	**result;

	result = ft_split(str, c);
	if (!result)
	{
		perror("split");
		exit(errno);
	}
	return (result);
}

char	*ft_protstrjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
	{
		perror("split");
		exit(errno);
	}
	return (result);
}


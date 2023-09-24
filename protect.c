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
		ft_error("split");
	return (result);
}

char	*ft_protstrjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		ft_error("strjoin");
	return (result);
}

int	protect_loop(int fd, char *line, char *argv)
{
	int	x;

	x = 1;
	if (ft_strncmp(line, argv, ft_strlen(argv)) == 0
		&& ft_strlen(line) - 1 == ft_strlen(argv))
		x = 0;
	if (x == 1)
		write(fd, line, ft_strlen(line));
	return (x);
}

void	ft_error(char *texto)
{
	perror(texto);
	exit(errno);
}

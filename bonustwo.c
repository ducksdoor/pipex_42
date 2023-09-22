/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonustwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:34:25 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/22 23:34:28 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_stop_pipex(int argc, char **argv, char **envp)
{
	char	*x;
	int		bool;
	int		fd;
	char	*line;

	bool = 1;
	x = argv[1];
	fd = ft_open(".aux", 2);
	while (bool == 1)
	{
		line = ft_get_next_line(0);
		write(fd, line, ft_strlen(line));
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) - 1) == 0)
			bool = 0;
	}
	if (argc == 6)
		ft_pipex(argv, envp);
	if (argc > 6)
		ft_big_pipex(argc, argv, envp);
	else
	{
		ft_printf("Necesito mas argumentos");
		exit(1);
	}
}
// to do ---> mandar bien los argv porque habra que cambiarlos. 
// to do 2 ---> poner cada escrita pipe heredoc>'??
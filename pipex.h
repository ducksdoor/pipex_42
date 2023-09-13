/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <lortega-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:16:55 by lortega-          #+#    #+#             */
/*   Updated: 2023/09/06 21:17:09 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# define READ_END	0
# define WRITE_END	1

void	ft_first_children(int *fd, int pid1, char **argv, char **envp);
void	ft_second_children(int *fd, int pid2, char **argv, char **envp);
void	ft_exe(char *command, char **envp);
char	*ft_search(char **env);
char	*ft_search2(char *object, char *command);
#endif

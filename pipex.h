
#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define READ_END	0
# define WRITE_END	1
# define FILE_NAME	"file.txt"

/* int main(void); */
int		main(int argc, char *argv[]);
void	ft_first_children(int *fd, int pid1, char *file, char *comand);
void	ft_second_children(int *fd, int pid2, char *file, char *comand);
#endif
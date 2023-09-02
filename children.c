
#include "pipex.h"
#include "libft/libft.h"

void	ft_first_children(int *fd, int pid1, char *file, char *comand)
{
	int		other_fd;
	char	*text_file;

	other_fd = open(file, O_RDONLY);
	if (other_fd == -1)
		exit(1);
	text_file = ft_get_next_line(other_fd);
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_printf("este es el proceso hijo1 y tiene que usar:  [%s] \n", comand);
		close(fd[1]);
	}
}
/* 		perror("execlp");
		exit(EXIT_FAILURE); */

void	ft_second_children(int *fd, int pid2, char *file, char *comand)
{
	if (!file || !comand)
		exit(1);
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}
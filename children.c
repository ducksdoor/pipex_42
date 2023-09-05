
#include "pipex.h"
#include "libft/libft.h"

void	ft_first_children(int *fd, int pid1, char *file, char *comand)
{
	int		other_fd;
	char	*text_file;

	// if (!comand)
	// 	exit(1);
	(void) comand;
	other_fd = open(FILE_NAME, O_RDWR);
	if (other_fd == -1)
//		exit(1);
		;
		(void) file;
	text_file = ft_get_next_line(other_fd);
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		//dup2(other_fd, fd[WRITE_END]);
		write(fd[WRITE_END], "culoooao", 8);
		close(fd[WRITE_END]);
		exit(0);
	}
}
/* 		perror("execlp");
		exit(EXIT_FAILURE); */

void	ft_second_children(int *fd, int pid2, char *file, char *comand)
{
	int	fd_dest;
	char	*buf;

	if (!file || !comand)
		//exit(1);
		;
	if (pid2 < 0)
		return ; 
	if (pid2 == 0)
	{
		fd_dest = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd[READ_END], STDIN_FILENO);
		dup2(fd_dest, STDOUT_FILENO);
		read(fd[READ_END], &buf, 8);
		write(fd_dest, &buf, 8);

//		close(fd[READ_END]); 
		/* close(fd[0]); */
		/* exit(0); */
	}
}
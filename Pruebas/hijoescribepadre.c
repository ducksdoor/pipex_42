
#include "pipex.h"

int main(void)
{
	int		fd[2];
	pid_t	pidC;
	char	buf[10];
	int		num;	

	pipe(fd);
	pidC = fork();
	if (pidC == -1)
		exit(2);
	if (pidC == 0)
	{
		close(fd[0]);
		write(fd[1], "abcde", 5);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd [1]);
		num = read(fd[0], buf, sizeof(buf));
		printf("Padre lee %d bytes: %s \n", num, buf);
		close(fd[0]);
	}
}

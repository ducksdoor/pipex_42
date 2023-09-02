#include "pipex.h"

	//el prototipo es:  ./pipex infile "ls -l" "wc -l" outfile
	//deberá hacer lo mismo que “<infile ls -l | wc -l >outfile”
//El programa tene que primero abrir un archivo infile del que va a leer,
// despues usar los dos comandos 
//y pegar el resultado en outfile

int hijopadre()
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

void	ft_open(char *file )
{
	int	fd;

	fd = 0;
	fd = open(file, O_RDONLY);
}

int	main(int argc, char *argv[])
{
	int	fd1[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			hijo_padre();
	}
}

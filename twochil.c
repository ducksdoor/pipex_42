
#include "pipex.h"

int main(int argc, char* argv[])
{
	int	fd1[2],  fd2; /*fd2 sera text.txt */
	int	status;
	int	pid;

	pipe (fd1); /* comunica ls y wc */
	
	pid = fork();
	if (pid == 0)   /* hijo 1, ejecuta "ls -l" */
	{
		close (fd1[READ_END]);

		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);

		execlp("/bin/ls", "ls", "-l", NULL);
	}
	else /* padre */
	{
		close(fd1[WRITE_END]); /* extremo no necesario ya */
	}
	pid = fork();

	if (pid == 0)   /* hijo 2, ejecuta "wc" */
	{
		fd2 = open(FILE_NAME, O_WRONLY);
		dup2(fd1[READ_END], STDIN_FILENO);
		close(fd1[READ_END]);

		dup2(fd2, STDOUT_FILENO);

		execlp("/usr/bin/wc", "wc", NULL);
	}
	else  /*padre*/
		close (fd1[READ_END]);   /* CERRAR EXTREMO no necesario */

	/* wait para cada hijo */
	wait(&status);
	wait(&status);
	return 0;
}
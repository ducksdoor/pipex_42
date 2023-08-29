#include "pipex.h"

#define SIZE 512

int main( int argc, char **argv )
{
	pid_t pid;
	int p[2], readbytes;
  char buffer[SIZE];
 
  pipe( p );
 
  if ( (pid=fork()) == 0 )
  { // hijo
    close( p[1] ); /* cerramos el lado de escritura del pipe */
 
    while( (readbytes=read( p[0], buffer, SIZE )) > 0)
      write( 1, buffer, readbytes );
 
    close( p[0] );
  }
  else
  { // padre
    close( p[0] ); /* cerramos el lado de lectura del pipe */
 
    strcpy( buffer, "Esto llega a traves de la tuberia\n" );
    write( p[1], buffer, strlen( buffer ) );
 
    close( p[1] );
  }
  waitpid( pid, NULL, 0 );
  exit( 0 );
}



/* 
//ejemplo 2
int main(void)
{
	int		fd[2];
	pid_t	pidC;
	char	buf[10];
	int		num;

	pipe(fd);
	pidC = fork();
	switch(pidC)
	{
		case 0:
			close(fd[0]);
			write(fd[1], "abcde", 5);
			close(fd[1]);
			exit(0);
			break;
		case -1:
			break;
		default:
			close(fd[1]);
			num = read(fd[0],buf,sizeof(buf));
			printf("Padre lee %d bytes: %s \n", num, buf);
			close(fd[0]);
			break;
	}
} */
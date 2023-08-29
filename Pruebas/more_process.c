#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_CHILD 5

int doSomething(void)
{
	int ret;
	srand(getpid());
	ret = (rand() % 256);
	printf("HIJO: ID= %d, valor aleatorio calculado %d \n", getpid(), ret);
	return ret;
}

int main(void)
{
	int	x;
	int	y;
	int status;
	pid_t pidC;

	x = 0;
	while (x < NUM_CHILD )
	{
		pidC = fork();
		if (pidC > 0)
		{
			continue;
		}
		else if (pidC == 0)
		{
			exit(doSomething());
		}
		else //error
		{}
		x++;
	}
	y = 0;
	x = 0;
	while ( x < NUM_CHILD )
	{
		pidC = wait(&status);
		printf("PADRE DE PID = %d, hijo de PID = %d terminado, st = %d \n", getpid(), pidC, WEXITSTATUS(status));
		y++;
	}
	while (1)
	{
		sleep (10);
	}
	return (0);
}
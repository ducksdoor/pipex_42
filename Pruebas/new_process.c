#include <unistd.h>
#include <stdio.h>

//Vamos a crear un proceso nuevo. Los dos procesos correran en espacios de memoria separados. 
//El proceso hijo es una copia del proceso padre.
//(tiene los mismos valores, pero los cambios que se realicen despues no influiran al otro).

int var = 22;

int main (void)
{
	pid_t	pidC; //algo asi como un entero con signo

	printf("** proc. PID = %d comienza ** \n", getpid());
	pidC = fork(); //fork crea un proceso nuevo y devuelve un valor
	//El valor que devuelve la funcion fork() sera un entero positivo que se mande al padre.


	//(la idea es que tengan distintos pid, uno por padre y otro por hijo)
	printf("proc. PID = %d, pidC = %d ejecutandose ** \n", getpid(), pidC);

	if (pidC > 0) // es el hijo y todo va bien
	{
		var = 44;
	}
	else if (pidC == 0) //ES EL PADRE
	{
		var = 33;
	}
	else //si es negativo, o simplemente -1 es error
	{

	}

	//Creamos un bucle infinito y hacemos que impriman por pantalla para saber que estan funcionando.
	while (1)
	{
		sleep(2);
		printf("proc. PID = %d, var = %d ejecutandose ** \n", getpid(), var);
	}
	return 0;
}
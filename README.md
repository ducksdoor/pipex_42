# pipex_42

### Fase de investigación:
  Por ahora que estoy documentandome voy a buscar información útil para el proyecto. La dejaré aquí escrita por si a alguien le sirve en un futuro. Aunque intento explicar como hacer los proyectos paso a paso. 

https://www.youtube.com/watch?v=oxWxcYoJJdM

  pipe es unidireccional, tiene una "entrada" y una "salida"

  se comunican bajo una relacción. (Padre hijo o hijo hijo)

  va asociado a dos fd (uno para leer y otro para leer)

pipe crea un  proceso Fork() para crear un proceso hijo, los dos procesos tendran el fd de open y de write abiertos. tendremos que cerrar uno de los opens y el write contrario.

segun el video seria algo como 

UNISTD
STDLIB
STDIO

int main(void)
{
  int fd[2];
  id_C pidC;
  char buf[10];
  int num;

  pipe (fd); to do --> si devuelve 0 todo esta bien si devuelve menos uno ha dado fallo....
  fork (); \\esto es una llamada al sistema
  pidC = fork();
  switch(pidC)
  {
    CASE 0:
    close(fd[0]); //el de lectura
    write(fd[1], "abcde", 5);
    close(fd[1]);
      BREAK;
    CASE -1;
  ---  EL HIJO NO SE HA CREADO---*to do error*
      breack
    default : //padre
      close(fd[1]);
      num = read(fd[0],buf,sizeof(buf) );
      printf(("Padre lee %d bytes: %s \n", num, buff)
      close(fd[0]);
      breack
  }  
}

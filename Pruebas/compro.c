
#include "pipex.h"

void pipex(int f1, int f2)
{
    int end[2];
    pipe(end);

    printf("Tubería creada con descriptores de archivo %d y %d\n", end[0], end[1]);

    // Aquí puedes realizar más operaciones utilizando los descriptores de archivo de la tubería
}

//prueba
/* int main(void)
{
    int file1 = 123;  // Reemplaza 123 con el descriptor de archivo válido
    int file2 = 456;  // Reemplaza 456 con el descriptor de archivo válido

    pipex(file1, file2);

    return 0;
} */
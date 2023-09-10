# pipex_42

![badge42](https://github.com/ducksdoor/pipex_42/assets/128644496/766bc96f-5dca-407e-a5f8-d2455489b1b4)
(ahora mismo esto es un caos, me gusta decir que es la lluvia de ideas de mi cabeza miestras busca información sobre como hacer este proyecto...)
#### introducción:
En UNIX/Linux. La línea de comandos pipex se utiliza para redirigir y ejecutar el flujo de datos entre dos comandos separados por un carácter '|', similar al operador de tubería en la línea de comandos. Deben crear un programa que tome cuatro argumentos de la línea de comandos: El nombre de un archivo de entrada, dos comandos separados por el carácter '|' y el nombre de un archivo de salida.
Usaremos.



###### Videos útiles: 
  - En este video nos explicaran como lanzar nuestros primeros procesos y datos super útiles para poder completar este proyecto.
https://www.youtube.com/watch?v=VwjP-KFuZCM
  - Esta es la segunda parte del video anterior, muy interesante y recomenable
https://www.youtube.com/watch?v=Dt9z_ohQWHI

###### Páginas útiles:
  - Si no te importa rebuscar y leer en la documentación siempre puedes entrar aqui.
https://man7.org/linux/man-pages/man7/man-pages.7.html

#### Datos que todo el mundo usa y que me ha costado que alguien me lo explique
--El dichoso numerito...
fd_dest = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    se refiere a los permisos que se están estableciendo para el archivo que se va a abrir o crear. En este caso, el número 0644 es una representación numérica de los permisos de archivo en sistemas Unix y Unix-like.
    El número 0644 se divide en tres partes:
    El primer dígito (0): Este dígito se refiere al tipo de archivo y a algunos bits especiales. En este caso, es 0, lo que significa que se trata de un archivo regular. Si fuera un directorio, sería 4.
    Los siguientes tres dígitos (644): Estos dígitos se refieren a los permisos específicos del archivo para diferentes tipos de usuarios (dueño, grupo y otros) en el sistema de archivos Unix. Cada dígito se descompone en bits para representar los permisos.
    El primer dígito (6) representa los permisos del propietario (dueño) del archivo. En este caso, 6 se traduce en binario como 110, lo que significa que el dueño tiene permisos de lectura y escritura (1 para lectura y 1 para escritura).
    Los siguientes dos dígitos (44) representan los permisos para el grupo y otros usuarios. En este caso, ambos son 4, lo que se traduce en binario como 100, lo que significa que tanto el grupo como otros usuarios solo tienen permiso de lectura (1 para lectura).
    En resumen, 0644 establece los siguientes permisos en el archivo:

    El dueño del archivo tiene permisos de lectura y escritura.
    El grupo y otros usuarios tienen permisos de solo lectura.


# Teoria necesaria para hacer este proyecto:

### - Descriptor de Archivo (files descriptor o FD):

En el contexto de Unix, la interacción con la entrada y la salida se basa en lo que se llama "descriptores de archivo" (FD). Unix tiene la característica de considerar casi todo en la computadora como un archivo, incluyendo el teclado y el monitor. Por lo tanto, escribir en la "pantalla" es, en realidad, escribir en un archivo que administra la presentación de datos en la pantalla, mientras que leer datos del teclado equivale a leer datos de un archivo que representa el teclado.

![pipe10-768x158](https://github.com/ducksdoor/pipex_42/assets/128644496/ac9d1bd3-64ae-4e3f-8ee8-1ae13a81ca40)

Los datos se transfieren a través de flujos, que son canales que mueven bytes de un lugar a otro. En el contexto de la entrada y salida, existen tres flujos predeterminados: la entrada estándar (stdin), la salida estándar (stdout) y el error estándar (stderr).

Estos tres flujos predeterminados se identifican mediante números de descriptor de archivo: stdin se asocia al número 0, stdout al número 1 y stderr al número 2. Un descriptor de archivo es un número entero que se vincula a un archivo abierto. Cada descriptor de archivo solo puede estar asociado a un archivo en un momento dado.

Además de los descriptores 0, 1 y 2, los procesos pueden usar otros descriptores de archivo según sus necesidades. Cuando se asigna un nuevo descriptor de archivo, se utiliza el número más bajo disponible que aún no ha sido asignado. En general, después de establecer los descriptores predeterminados 0, 1 y 2, el siguiente en la línea suele ser el descriptor 3.  

### - Flujo de datos (Data flow)



El proceso que se crea para cada comando debe saber qué datos, si los hay, tomar como entrada y posiblemente qué datos generar como salida. El proceso de cada comando también debe saber dónde enviar y recibir tales datos. Por lo general, los datos que fluyen "hacia" algo se consideran entrada y los datos que fluyen "desde" algo se consideran salida. Dicho de otra manera: la entrada se lee desde algún lugar; la salida se escribe en algún lugar. 

Algo importante a tener en cuenta es que en realidad hay dos flujos que pueden escribir salida en la terminal de manera predeterminada: stdout y stderr. (El flujo stderr se utiliza cuando algo sale mal al intentar ejecutar un comando.)

![pipe11-768x155](https://github.com/ducksdoor/pipex_42/assets/128644496/0ad63be6-9fc2-4a29-97f7-0dc5be577eb6)

se puede definir la entrada de un comando como los datos que se pasan específicamente utilizando stdin ya sea que se escriban mediante el teclado, se redirijan mediante redirección de E/S (explicada más adelante) o posiblemente se pasen al comando como un argumento de archivo.

Como ejemplos curiosos de flujos de datos tenemos los casos que no reciben entrada pero provocan salida y los casos que no reciben ni entrada ni salida:

  - Si un comando no acepta entrada desde stdin, los datos pasados a dicho comando simplemente serán ignorados por el programa que ejecuta el comando, ya que no está diseñado para manejar datos de entrada. Por ejemplo, < words.txt ls listará los archivos y directorios en el directorio actual e ignorará la entrada que fue redirigida a stdin

  - mv no requiere entrada y no produce salida: Si le doy el nombre de un archivo o directorio que pueda ser movido o renombrado con éxito, entonces no se emite ningún dato a través de stdout o stderr. Recuerda que, dado que el contenido de este archivo no se está leyendo ni utilizando de ninguna manera, el archivo que se pasa no se considera entrada. Sin embargo, si uso mv de manera incorrecta y ocurre un error, entonces habrá una salida en stderr:

  - Los pipes (|) permiten que la salida de un proceso se pase como entrada a otro proceso y mediante redirección de E/S (I/O redirection), se consigue que los archivos sean la fuente y el destino de datos en lugar del teclado y la terminal por defecto.

### - Introducción a Pipes

  - Las tuberías permiten que los datos de un proceso se pasen a otro (a través de un flujo unidireccional de datos)
  - Esta concatenación de procesos puede representarse mediante un conducto: los comandos en un conducto están conectados mediante tuberías, donde los datos se comparten entre procesos al fluir desde un extremo de la tubería hasta el otro. (aunque cada proceso (comando) se ejecuta con un espacio de memoria separado. En realidad son flujos con búfer asociados con dos descriptores de archivo que se configuran de manera que el primero pueda leer los datos escritos en el segundo.

<img width="1000" alt="pipe" src="https://github.com/ducksdoor/pipex_42/assets/128644496/72f15613-13ce-466e-839f-49d61c60a2f0">

Supongamos que en el código que ejecuta los comandos en el conducto, la llamada a pipe() llena un array de descriptores de archivo {3, 4} de manera que los datos escritos en 4 puedan leerse desde 3. 
El propósito de cada file descriptor depende de qué índice ocupe en el array. hay que destacar que como los descriptores de fichero de UNIX son simplemente enteros, un pipe o tubería no es más que un array de dos enteros:

### Explicación de las funciones

  ### - pipe(): 
    toma un array de dos enteros, como por ejemplo int end[2], y los conecta entre sí. En una tubería, lo que se hace en end[0] es visible en end[1]
    Además, pipe() asigna un fd  a cada extremo.      

### Ejecutando Comandos en un Conducto

     Por lo general, el proceso padre realiza cualquier configuración necesaria y luego crea un proceso hijo mediante una llamada fork(), que crea un clon del estado de memoria y los descriptores de archivo del proceso padre.
     Después de la llamada a fork(), los cambios en el proceso padre no serán visibles para el proceso hijo y viceversa.     
     
     
     
<img width="1526" alt="Screen Shot 2023-08-29 at 8 50 31 PM" src="https://github.com/ducksdoor/pipex_42/assets/128644496/67bb1fdc-ad87-418d-8d53-8c6997807d08">


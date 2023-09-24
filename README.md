# pipex_42

![badge42](https://github.com/ducksdoor/pipex_42/assets/128644496/766bc96f-5dca-407e-a5f8-d2455489b1b4)

<font color="green">
No es oro todo lo que reluce,

ni toda la gente errante anda perdida;</font>

# INDICE! 

Introducción:

- [🦆 De mi Para ti](#-de-mi-para-ti)
- [Introducción](#introducción)

Documentación:

- [Videos útiles](#videos-útiles)
  - [Explicaciones en español](#explicaciones-en-español)
  - [Explicaciones en inglés](#explicaciones-en-inglés)
- [Páginas útiles](#páginas-útiles)
- [Datos útiles](#datos-útiles)
  - [El dichoso numerito](#el-dichoso-numerito)
- [Teoría necesaria para hacer este proyecto](#teoría-necesaria-para-hacer-este-proyecto)
  - [Descriptor de Archivo (files descriptor o FD)](#descriptor-de-archivo-files-descriptor-o-fd)
  - [Flujo de datos (Data flow)](#flujo-de-datos-data-flow)
  - [Introducción a Pipes](#introducción-a-pipes)
  - [Funciones](#funciones)

Proyecto:
- [Código personal](#Código-personal)
- [Parseo](#Parseo)
- [Pruebas típicas](#Pruebas-típicas)
- [Comandos útiles](Comandos-útiles)



# 🦆 De mi Para ti:
Con esto quiero decire que esta bien rebuscar información. Es más, te invito a ello. Esta bien perder el tiempo intentando cosas y practicando, probando ideas que no terminan de funcionar y rectificando para conseguir tu objetivo.
Te dejo otra mini "Guia", no para que la copies sin sentido si no para intentar ayudarte a razonar. Para lo poco que se de programación me he encontrado muchas veces buscando información en internet, a veces con buenos resultados y otras perdiendo el tiempo, pero esto sigue siendo una habilidad que tendras que desarrollar. No voy a dejar un readmi para todo lo que hagas en la vida. Usa videos, este documento o lo que necesites. __Pero aprende!__

# introducción:
En UNIX/Linux. La línea de comandos pipex se utiliza para redirigir y ejecutar el flujo de datos entre dos comandos separados por un carácter '|', similar al operador de tubería en la línea de comandos. Deben crear un programa que tome cuatro argumentos de la línea de comandos: El nombre de un archivo de entrada, dos comandos separados (con o sin añadidos y estando entre comillas cada uno, ejemplo: ./pipex "ls -a" "wc -l" y el nombre de un archivo de salida.

<img width="1526" alt="Screen Shot 2023-08-29 at 8 50 31 PM" src="https://github.com/ducksdoor/pipex_42/assets/128644496/67bb1fdc-ad87-418d-8d53-8c6997807d08">
Esta imagen es de WhileTrueThenDream (youtuber)

# Videos útiles:
### Explicaciones en español
  - En este video nos explicaran como lanzar nuestros primeros procesos y datos super útiles para poder completar este proyecto.
https://www.youtube.com/watch?v=VwjP-KFuZCM
  - Esta es la segunda parte del video anterior, muy interesante y recomenable
https://www.youtube.com/watch?v=Dt9z_ohQWHI

### Explicaciones en ingles
  - Aqui esta para un solo pipe https://www.youtube.com/watch?v=6xbLgZpOBi8&ab_channel=CodeVault

Aunque este chico sube videos super interesantes, para este proyecto te pueden interesar los siguientes:

  - https://www.youtube.com/watch?v=NkfIUo_Qq4c&ab_channel=CodeVault (que habla de multiples pipes)
  - https://www.youtube.com/watch?v=94URLRsjqMQ&list=RDCMUC6qj_bPq6tQ6hLwOBpBQ42Q&start_radio=1&rv=94URLRsjqMQ&t=0&ab_channel=CodeVault (que habla de los forks...)

__Hay muchos, os vuelvo a invitar a que investigueis, al final, todo lo que aprendais es para vosotr@s__

### Páginas útiles:

  - https://www.rozmichelle.com/pipes-forks-dups/
  - https://www.programacion.com.py/escritorio/c/pipes-en-c-linux
  - https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901

  - Si no te importa rebuscar y leer en la documentación siempre puedes entrar aqui.
https://man7.org/linux/man-pages/man7/man-pages.7.html

# Datos utiles
#### __El dichoso numerito__

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

 ### __Descriptor de Archivo (files descriptor o FD)__

En el contexto de Unix, la interacción con la entrada y la salida se basa en lo que se llama "descriptores de archivo" (FD). Unix tiene la característica de considerar casi todo en la computadora como un archivo, incluyendo el teclado y el monitor. Por lo tanto, escribir en la "pantalla" es, en realidad, escribir en un archivo que administra la presentación de datos en la pantalla, mientras que leer datos del teclado equivale a leer datos de un archivo que representa el teclado.

![pipe10-768x158](https://github.com/ducksdoor/pipex_42/assets/128644496/ac9d1bd3-64ae-4e3f-8ee8-1ae13a81ca40)

Los datos se transfieren a través de flujos, que son canales que mueven bytes de un lugar a otro. En el contexto de la entrada y salida, existen tres flujos predeterminados: la entrada estándar (stdin), la salida estándar (stdout) y el error estándar (stderr).

Estos tres flujos predeterminados se identifican mediante números de descriptor de archivo: stdin se asocia al número 0, stdout al número 1 y stderr al número 2. Un descriptor de archivo es un número entero que se vincula a un archivo abierto. Cada descriptor de archivo solo puede estar asociado a un archivo en un momento dado.

Además de los descriptores 0, 1 y 2, los procesos pueden usar otros descriptores de archivo según sus necesidades. Cuando se asigna un nuevo descriptor de archivo, se utiliza el número más bajo disponible que aún no ha sido asignado. En general, después de establecer los descriptores predeterminados 0, 1 y 2, el siguiente en la línea suele ser el descriptor 3.  


### __Flujo de datos (Data flow)__



El proceso que se crea para cada comando debe saber qué datos, si los hay, tomar como entrada y posiblemente qué datos generar como salida. El proceso de cada comando también debe saber dónde enviar y recibir tales datos. Por lo general, los datos que fluyen "hacia" algo se consideran entrada y los datos que fluyen "desde" algo se consideran salida. Dicho de otra manera: la entrada se lee desde algún lugar; la salida se escribe en algún lugar. 

Algo importante a tener en cuenta es que en realidad hay dos flujos que pueden escribir salida en la terminal de manera predeterminada: stdout y stderr. (El flujo stderr se utiliza cuando algo sale mal al intentar ejecutar un comando.)

![pipe11-768x155](https://github.com/ducksdoor/pipex_42/assets/128644496/0ad63be6-9fc2-4a29-97f7-0dc5be577eb6)

se puede definir la entrada de un comando como los datos que se pasan específicamente utilizando stdin ya sea que se escriban mediante el teclado, se redirijan mediante redirección de E/S (explicada más adelante) o posiblemente se pasen al comando como un argumento de archivo.

Como ejemplos curiosos de flujos de datos tenemos los casos que no reciben entrada pero provocan salida y los casos que no reciben ni entrada ni salida:

  - Si un comando no acepta entrada desde stdin, los datos pasados a dicho comando simplemente serán ignorados por el programa que ejecuta el comando, ya que no está diseñado para manejar datos de entrada. Por ejemplo, < words.txt ls listará los archivos y directorios en el directorio actual e ignorará la entrada que fue redirigida a stdin

  - mv no requiere entrada y no produce salida: Si le doy el nombre de un archivo o directorio que pueda ser movido o renombrado con éxito, entonces no se emite ningún dato a través de stdout o stderr. Recuerda que, dado que el contenido de este archivo no se está leyendo ni utilizando de ninguna manera, el archivo que se pasa no se considera entrada. Sin embargo, si uso mv de manera incorrecta y ocurre un error, entonces habrá una salida en stderr:

  - Los pipes (|) permiten que la salida de un proceso se pase como entrada a otro proceso y mediante redirección de E/S (I/O redirection), se consigue que los archivos sean la fuente y el destino de datos en lugar del teclado y la terminal por defecto.
    
### __Introducción a Pipes__

  - Las tuberías permiten que los datos de un proceso se pasen a otro (a través de un flujo unidireccional de datos)
  - Esta concatenación de procesos puede representarse mediante un conducto: los comandos en un conducto están conectados mediante tuberías, donde los datos se comparten entre procesos al fluir desde un extremo de la tubería hasta el otro. (aunque cada proceso (comando) se ejecuta con un espacio de memoria separado. En realidad son flujos con búfer asociados con dos descriptores de archivo que se configuran de manera que el primero pueda leer los datos escritos en el segundo.

<img width="1000" alt="pipe" src="https://github.com/ducksdoor/pipex_42/assets/128644496/72f15613-13ce-466e-839f-49d61c60a2f0">

Supongamos que en el código que ejecuta los comandos en el conducto, la llamada a pipe() llena un array de descriptores de archivo {3, 4} de manera que los datos escritos en 4 puedan leerse desde 3. 
El propósito de cada file descriptor depende de qué índice ocupe en el array. hay que destacar que como los descriptores de fichero de UNIX son simplemente enteros, un pipe o tubería no es más que un array de dos enteros:

# Funciones

__Pipe()__ 

es una función de sistema en C que se utiliza para crear un pipe o tubería entre dos procesos.

La función acepta un array de enteros de dos elementos. Después de la llamada a pipe, el primer elemento del array almacena el descriptor de archivo utilizado para leer datos desde el pipe y el segundo elemento del array almacena el descriptor de archivo utilizado para escribir datos en el pipe.

La función pipe devuelve un valor entero, -1 si hay un error y 0 si la llamada es exitosa. Los posibles errores incluyen la falta de recursos del sistema, como la memoria, o la falta de permisos para crear un pipe.

__Fork()__

es una función de sistema en C que se utiliza para crear un nuevo proceso. Después de una llamada a fork, el proceso original se divide en dos procesos diferentes: el proceso padre y el proceso hijo. Ambos procesos tienen un flujo de ejecución independiente y se ejecutan en paralelo.

La función fork no tiene argumentos y devuelve un valor entero. En el proceso padre, el valor devuelto es el PID (identificador de proceso) del proceso hijo, y en el proceso hijo, el valor devuelto es 0. Si ocurre un error durante la creación del nuevo proceso, fork devuelve -1.

El proceso hijo creado por fork es una copia exacta del proceso padre, incluyendo el código, los datos y el estado del proceso. Sin embargo, hay algunas diferencias importantes entre el proceso hijo y el proceso padre. Por ejemplo, el PID del proceso hijo es diferente del PID del proceso padre y los valores de retorno de fork son diferentes para el proceso hijo y el proceso padre.

__perror()__

toma como argumento una cadena de caracteres y escribe en la salida estándar de error (stderr) la cadena de caracteres seguida de un dos puntos, un espacio y el mensaje de error correspondiente a la última llamada al sistema que falló. El mensaje de error se obtiene a partir del valor de la variable global errno.

__La línea de código exit(errno)__

Después de imprimir el mensaje de error, la función error llama a la función exit() para salir del programa con un código de error (EXIT_FAILURE). El código de error indica que el programa ha fallado y puede ser utilizado por el sistema operativo para identificar el tipo de error que se produjo durante la ejecución del programa.


__dup2()__

int dup2(int oldfd, int newfd). En el contexto del programa pipex, la función dup2() se utiliza para redirigir la entrada o salida estándar de un proceso a través del uso de pipes. Por ejemplo, en la función child(), dup2(fd[1], STDOUT_FILENO) redirige la salida estándar del proceso hijo al extremo de escritura del pipe, mientras que dup2(filein.txt, STDIN_FILENO) redirige la entrada estándar del proceso hijo al descriptor de archivo filein, que representa el archivo de entrada especificado en el comando.

__execv()__

Se utiliza para reemplazar la imagen de un proceso actual con una nueva imagen de proceso. Esta nueva imagen de proceso se carga desde un archivo ejecutable especificado. Es comúnmente utilizada para ejecutar otros programas desde dentro de un programa existente.

La función execv() toma tres argumentos: el primero es la ruta al archivo ejecutable que se desea ejecutar, el segundo es un array de punteros a cadenas de caracteres que representan los argumentos pasados al programa. El último elemento de este array de argumentos debe ser NULL para indicar el final de la lista de argumentos. (Podemos usar el env).

Después de una exitosa llamada a execv(), el programa actual se detiene y es reemplazado por el nuevo programa. El nuevo programa hereda el descriptor de archivo, el entorno y otros atributos del proceso original. Esto significa que puede continuar ejecutándose con los mismos recursos y el mismo entorno, pero con una nueva imagen de programa.

Es importante destacar que si execv() tiene éxito, el proceso actual no continúa ejecutándose más allá de esa llamada, a menos que haya un error en la ejecución del nuevo programa. Si execv() falla, generalmente devuelve -1 y el proceso actual continúa ejecutándose normalmente.

En resumen, execv() es una función esencial para la creación de nuevos procesos dentro de un programa existente, ya que permite cargar y ejecutar programas externos en el contexto de ese programa. Esto es útil para la creación de sistemas más complejos que involucran múltiples programas y procesos.
     
__waitpid()__

Se utiliza para esperar a que un proceso hijo específico termine y obtener información sobre su estado de finalización.

Toma tres argumentos principales:

pid: El PID del proceso hijo que se desea esperar.
status: Un puntero donde se almacena la información del estado del proceso hijo.
options: Banderas que controlan el comportamiento de la espera.
Después de una llamada exitosa a waitpid():

Retorna el PID del proceso hijo que finalizó.
El estado del proceso hijo se almacena en status, incluyendo su código de salida y si finalizó normalmente o debido a una señal.
Si no hay proceso hijo que coincida con el PID especificado y se usa WNOHANG, waitpid() retorna 0.

En caso de error, waitpid() retorna -1.

En resumen, waitpid() permite a un proceso padre esperar y obtener información sobre procesos hijos específicos, ofreciendo un mayor control y gestión de procesos en programas escritos en C.

__access()__

Se usa para verificar si un archivo o directorio es accesible con los permisos especificados. Se encuentra en la biblioteca unistd.h.
Argumentos:
pathname: Ruta al archivo o directorio que se desea verificar.
mode: Modo de acceso que se quiere verificar (por ejemplo, R_OK para legibilidad, W_OK para escritura, X_OK para ejecución).
Valor de Retorno:

Devuelve 0 si el acceso se verifica con éxito (cumple con los permisos especificados).
Devuelve -1 si falla y establece errno con un código de error específico.
Uso Típico: Utilizado para verificar los permisos de un archivo o directorio antes de realizar operaciones en él, como leer o escribir.


# Código Personal

Este proyecto ha sido mas cortito en código, aunque a cambio, ha sido mas largo en busqueda de información. Teniendo que buscar que hacía cada función y no creandolas. Un pequeño resumen de los archivos seria el siguiente:

__Makefile y pipex.h__

- Son los encargados de guardar las reglas de compilación y hacer por tanto que todo este funcionando. 

__pipex.c__

- En este archivo está el main. Desde el, se inicia el programa, tendriamos como tres ejecuciones, la normal y los dos bonus. En este archivo esta programada la ejecucion normal y el bonus de here_doc.

__bonus.c__

- Aquí se guardan los cambios necesarios de la función original para poder usar varios pipex con varios comandos, es decir, el bonus del proyecto

__utils.c y protect.c__

- Son las funciones necesarias, tanto para el buen funcionamiento del proyecto, como para las protecciones necesarias del mismo. En utils por ejemplo esta programada toda la busqueda del PATH y la gestión de los comandos que añades en la terminal.

# Parseo

__PATH=__

- La función exeve necesita encontrar las rutas en las que se encuentran los ejecutables de los comandos que vamos a usar, (como por ejemplo ls, wc, cat...) Para ello lo buscara en el env.

- Tendremos que encontrar el Path, que sera algo parecido a PATH=/Users/lortega-/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki. Esto es sencillo de encontrar buscando en la variable **env el principio de linea (ft_search)

- Una vez que tengamos esto, podremos usar la funión split para separar cada una de las rutas. Si a estas rutas las unimos con los comandos podremos probar con la función access si hemos encontrado la ruta valida.

__Comandos__

- Los comandos pueden venir como rutas relativas (ls) o absulatas ("/bin/wc"). Ademas, pueden venir con flags ("cat -e") o con los añadidos necesarios como ("grep hola"), si el comando que te se introduce necesita poner un espacio para completarse ("ls -l") se tendra que introducir entre dobles comillas. Si viene entre comillas tendras que usar split en el comando.

__access__

- Ahora que tenemos tanto el path como el comando se puede usar acces, simplemente tendremos que conseguir algo parecido a /bin/ls en cualquiera de las opciones

# Pruebas típicas

- No tener acceso a los archivos o que no existen, por tanto tiene que dar error.

- Quitar el env con la linea __unset PATH__ y probar que no acepta comandos sin ruta como "ls", a no ser que se introduzca el comando en la carpeta de ejecución, como bash añade directamente el ./ aunque no lo tenga escrito, se tendrá que haber puesto en el código entregado.

- Para el bonus poner muchas veces cat por ejemplo, tendra que funcionar igualmente.

# Comandos útiles

  void	leaks(void)
  {
	  system("leaks -q pipex");
  }

  	atexit(leaks);
# Biblioteca de Sincronización de Hilos
Este repositorio contiene la implementación de una biblioteca con herramientas para la sincronización de hilos en C.

## Tabla de Contenidos
- [Requisitos](#requisitos)
- [Herramientas](#herramientas)
  - [Barrera](#barrera)
  - [Semáforo](#semáforo)
  - [Read/Write Lock](#readwrite-lock)
- [Uso](#uso)
- [Ejemplos](#ejemplos)

## Requisitos
Para utilizar la biblioteca se deben cumplir los siguientes requisitos:
1. Un sistema operativo Linux.
2. GCC instalado en la distribución de Linux.
3. Make instalado en la distribución de Linux.

## Herramientas
La biblioteca permite trabajar con tres herramientas clásicas para la sincronización de hilos, las cuales
son la barrera, el semáforo y el read/write lock. Las implementaciones de las tres herramientas se encuentran
en el archivo *sync_lib.c*, y los prototipos de funciones y definiciones de estructuras se encuentran en el
archivo *sync_lib.h*.

### Barrera
La barrera es una herramienta de sincronización, se utiliza en contextos donde hay un contexto de datos en paralelo en el que diferentes subprocesos realizan las mismas operaciones en diferentes subconjuntos de un conjunto de datos global. Lo que diferencia a la barrera de otras herramientas de sincronización, es que esta es utilizada de manera que permite que inicien *n* cantidad de subprocesos, todos ejecutándose al mismo tiempo, después genera una barrera para que los subprocesos no puedan continuar con su ejecución hasta que todos hayan alcanzado cierto punto de ejecución, en ese momento ya pueden seguir al mismo tiempo sus tareas. 

La biblioteca cuenta con las siguientes funciones para trabajar con la barrera:

#### Barrier *create_barrier(int counter)
Recibe un entero, el cual es el valor inicial para el contador de la barrera. La función crea un mutex
y una variable de condición para la barrera, además de configurar el contador y asignar memoria dinámica para la barrera. La función retorna
un puntero a la nueva barrera. **Utilice esta operación para crear una nueva barrera**.

#### void wait_barrier(Barrier *b)
Recibe un puntero a una barrera. La función disminuye el contador de hilos. Si el contador no ha llegado a cero, el hilo espera en la variable de condición. Cuando el contador llega a cero, la función envía una señal a los demás hilos para que puedan continuar con su ejecución y se libera el mutex. **Utilice esta operación para asegurarse de que todos los hilos lleguen a un punto específico antes de continuar**.

#### void destroy_barrier(Barrier *b)
Recibe un puntero a una barrera. La función destruye el mutex y la variable de condición, además de liberar
la memoria dinámica asignada a la barrera. **Utilice esta operación para destruir una barrera que ya no va a ser utilizada**.

### Semáforo
El semáforo es una herramienta que permite bloquear el acceso a regiones críticas a solo cierta cantidad
de hilos, además de permitir la coordinación entre varios hilos, es decir, un hilo puede utilizar operaciones
del semáforo de otro hilo. La estructura del semáforo se compone de un contador para controlar la cantidad de
hilos que acceden a un recurso, un mutex para garantizar que las operaciones del semáforo sean accedidas solo por un hilo a la vez, y una variable de condición 
para poder bloquear y desbloquear hilos del semáforo.

La biblioteca provee las siguientes operaciones para trabajar con semáforos:

#### Semaphore *create_semaphore(int counter)
Recibe un entero, el cual es el valor inicial para el contador del semáforo. La función crea un mutex
y una variable de condición para el semáforo, además de configurar el contador y asignar memoria dinámica para el semáforo. La función retorna
un puntero al semáforo. **Utilice esta operación para crear un nuevo semáforo**.

#### void destroy_semaphore(Semaphore *sem)
Recibe un puntero a un semáforo. La función destruye el mutex y la variable de condición, además de liberar
la memoria dinámica asignada al semáforo. **Utilice esta operación para destruir un semáforo que ya no va a ser utilizado**.

#### void wait_semaphore(Semaphore *sem)
Recibe un puntero a un semáforo. La función verifica si existe espacio para el hilo según el contador. Si el contador es cero, entonces
bloquea al hilo hasta que se haya liberado un recurso del semáforo. Si el contador no es cero, o el semáforo fue desbloqueado, entonces decrementa el contador y permite
al hilo acceder al recurso. **Utilice esta operación para pedir acceso a un recurso del semáforo antes de ingresar a una región crítica**.

#### void signal_semaphore(Semaphore *sem)
Recibe un puntero a un semáforo. La función incrementa el contador y despierta a un hilo bloqueado para que acceda al recurso (si los hay).
**Utilice esta operación para liberar un recurso del semáforo tras terminar la región crítica**.

### Read/Write Lock
El Read/Write Lock es un mecanismo de sincronización que optimiza el rendimiento al permitir que múltiples hilos accedan simultáneamente al recurso en modo lectura, siempre y cuando no haya hilos realizando escrituras. Sin embargo, cuando un hilo necesita escribir en el recurso, el ReadWrite Lock asegura que ningún otro hilo pueda leer ni escribir hasta que la operación de escritura se complete. La estructura del Read/Write Lock se compone de un mutex para proteger el acceso de variables compartidas, dos variables de condición para coordinar la espera de lectores y escritores, y tres contadores que llevan un registro del número de lectores y escritores activos, así como del número de escritores que están esperando para acceder al recurso.

La biblioteca provee las siguientes operaciones para trabajar con Read/Write Lock:

#### ReadWriteLock *create_read_write_lock()
Esta función crea e inicializa la estructura ReadWriteLock. Asigna memoria para el bloqueo, inicializa el mutex y las variables de condición para lectores y escritores, y configura los contadores de lectores y escritores en 0. Finalmente devuelve un puntero a la estructura ReadWriteLock. **Utilice esta operación para crear y configurar un nuevo ReadWriteLock antes de usarlo**

#### void destroy_read_write_lock(ReadWriteLock *rw_lock) 
Esta función destruye el ReadWriteLock. Recibe un puntero a la estructura como parámetro, destruye el mutex y las variables de condición, y libera la memoria asignada para la estructura ReadWriteLock. **Utilice esta operación para liberar los recursos asociados con un ReadWriteLock cuando ya no se necesite**

#### void lock_read(ReadWriteLock *rw_lock)
Esta función bloquea el acceso de lectura. Recibe un puntero a un ReadWriteLock y, si no hay escritores activos o pendientes, incrementa el contador de lectores activos, permitiendo el acceso de lectura. Si hay escritores, el hilo espera hasta que el acceso sea seguro. **Utilice esta operación para asegurar que múltiples hilos puedan leer un recurso simultáneamente cuando no haya escritores**

#### void unlock_read(ReadWriteLock *rw_lock)
Esta función libera el bloqueo de lectura. Recibe un puntero a un ReadWriteLock, decrementa el contador de lectores activos y, si no quedan más lectores y hay escritores pendientes, despierta a un escritor para que pueda continuar. **Utilice esta operación para liberar el acceso de lectura y permitir que otros hilos accedan al recurso**

#### void lock_write(ReadWriteLock *rw_lock)
Esta función bloquea el acceso de escritura. Recibe un puntero a un ReadWriteLock y si hay lectores o escritores activos, incrementa el contador de escritores pendientes y espera hasta que el recurso esté disponible. Una vez seguro, decrementa los escritores pendientes y aumenta los escritores activos. **Utilice esta operación para obtener un acceso exclusivo de escritura a un recurso compartido**


#### void unlock_write(ReadWriteLock *rw_lock)
Esta función libera el bloqueo de escritura. Recibe un puntero a un ReadWriteLock, decrementa el contador de escritores activos y, si hay escritores pendientes, despierta a uno. Si no hay escritores pendientes, permite que los lectores accedan al recurso. **Utilice esta operación para liberar el acceso de escritura y permitir que otros hilos accedan al recurso, ya sea leer o escribir**


## Uso

Para usar la biblioteca debe descargar los archivos [sync_lib.o](sync_lib.o) y *sync_lib.h* de este repositorio. Cuando haga su programa,
debe incluir los archivos descargados en la misma carpeta donde vaya a compilar su programa. Además, debe incluir el encabezado
de la biblioteca en los archivos donde la vaya a usar de la siguiente forma:

```c
#include "sync_lib.h"
```

Cuando haga la compilación, la debe hacer de la siguiente forma:

```bash
gcc -o miPrograma miPrograma.c sync_lib.o
```

Si utiliza algún entorno de desarrollo también puede utilizar las rutas de los archivos para configurar el *linker* y el
compilador para encontrar el encabezado y el archivo objeto de la biblioteca. De este modo no es necesario tener los
archivos de la biblioteca en la misma carpeta de su programa, pues el entorno de desarrollo utiliza las rutas para encontrar los archivos.

## Ejemplos

En el repositorio encontrará tres archivos (*barrier_example.c*, *semaphore_example.c*, *rwlock_example.c*), cada uno con un ejemplo de uso de una de las estructuras de la biblioteca. Para ejecutar los ejemplos deberá descargar los archivos de los ejemplos y los archivos *sync_lib.o* y *sync_lib.h*, 
además del archivo *Makefile*. Todos estos archivos deben estar en una misma carpeta.

Para ejecutar los ejemplos, abra una terminal en la carpeta y use los siguientes comandos para cada ejemplo:

### Barrera
```bash
make barrier_example
```

### Semáforo
```bash
make semaphore_example
```

### Read/Write Lock
```bash
make rwlock_example
```

El *Makefile* se encarga de compilar el ejemplo, ejecutar el programa y limpiar los archivos creados tras finalizar la ejecución. Si inspecciona
este archivo, podrá notar que los ejemplos se compilan de la misma forma en la que se explicó en este *readme*.

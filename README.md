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
en el archivo 'sync_lib.c', y los prototipos de funciones y definiciones de estructuras se encuentran en el
archivo 'sync_lib.h'.

### Barrera

### Semáforo
El semáforo es una herramienta que permite bloquear el acceso a regiones críticas a solo cierta cantidad
de hilos, además de permitir la coordinación entre varios hilos, es decir, un hilo puede utilizar operaciones
del semáforo de otro hilo. La estructura del semáforo se compone de un contador para controlar la cantidad de
hilos que acceden a un recurso, un mutex para garantizar que las operaciones del semáforo sean atómicas, y una variable de condición 
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
al hilo acceder al recurso. **Utilice esta operación para controlar el acceso de los hilos a una región crítica**.

#### void signal_semaphore(Semaphore *sem)
Recibe un puntero a un semáforo. La función incrementa el contador y despierta a un hilo bloqueado para que acceda al recurso (si los hay).
**Utilice esta operación cuando los hilos terminen de trabajar en la región crítica**.

### Read/Write Lock

## Uso

## Ejemplos

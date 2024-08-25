// --------------------------------------------------------
// Este archivo contiene los prototipos de las funciones
// para la biblioteca de sincronización de hilos y las
// definiciones de los tipos de datos necesarios para
// manejar las estructuras de sincronización
// --------------------------------------------------------

#include <pthread.h>

// --------------------------------------------------------
// BARRERA
// --------------------------------------------------------

typedef struct {
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Barrier;

Barrier *create_barrier(int count);
void wait_barrier(Barrier *b);
void destroy_barrier(Barrier *b);

// --------------------------------------------------------
// SEMÁFORO
// --------------------------------------------------------

typedef struct {
  int counter;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Semaphore;

Semaphore *create_semaphore(int counter);
void destroy_semaphore(Semaphore *sem);
void wait_semaphore(Semaphore *sem);
void signal_semaphore(Semaphore *sem);

// --------------------------------------------------------
// R/W LOCK
// --------------------------------------------------------

typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond_readers;
  pthread_cond_t cond_writers;
  int active_readers;
  int active_writers;
  int pending_writers;
} ReadWriteLock;

ReadWriteLock *create_read_write_lock();
void destroy_read_write_lock(ReadWriteLock *rw_lock);
void lock_read(ReadWriteLock *rw_lock);
void unlock_read(ReadWriteLock *rw_lock);
void lock_write(ReadWriteLock *rw_lock);
void unlock_write(ReadWriteLock *rw_lock);
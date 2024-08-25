#include "sync_lib.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ReadWriteLock *rw_lock;

void *reader(void *arg) {
  printf("Lector: Esperando para adquirir el bloqueo de lectura...\n");
  lock_read(rw_lock);
  printf("Lector: Bloqueo de lectura adquirido.\n");
  sleep(1);
  unlock_read(rw_lock);
  printf("Lector: Liberado bloqueo de lectura.\n");

  return NULL;
}

void *writer(void *arg) {
  printf("Escritor: Esperando para adquirir el bloqueo de escritura...\n");
  lock_write(rw_lock);
  printf("Escritor: Bloqueo de escritura adquirido.\n");
  sleep(1);
  unlock_write(rw_lock);
  printf("Escritor: Liberado el bloqueo de escritura.\n");

  return NULL;
}

int main() {
  pthread_t reader_thread;
  pthread_t writer_thread;

  rw_lock = create_read_write_lock();

  // Hilo de lectura
  pthread_create(&reader_thread, NULL, (void *)reader, NULL);

  // Hilo de escritura
  pthread_create(&writer_thread, NULL, (void *)writer, NULL);

  pthread_join(reader_thread, NULL);
  pthread_join(writer_thread, NULL);

  destroy_read_write_lock(rw_lock);
  
  return 0;
}

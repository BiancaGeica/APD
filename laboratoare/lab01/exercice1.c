#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 8

void *f(void *arg) {
  long id = *(long *)arg;
  printf("Hello World din thread-ul %ld!\n", id);
  pthread_exit(NULL); 
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS]; // vector cu id-ul fiecarui thread creat
  int r; // starea thread-ului dupa creare, daca este diferit de 0, ceva nu a mers ok
  long id; // variabila pentru ciclarea prin thread-uri
  void *status;
  long ids[NUM_THREADS];

  for (id = 0; id < NUM_THREADS; id++) {
    ids[id] = id; // stocam id-ul fiecarui thread creat in acest moment
    r = pthread_create(&threads[id], NULL, f, &ids[id]); // creem thread-ul, apoi in r salvam starea dupa creare

    if (r) {
      printf("Eroare la crearea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  for (id = 0; id < NUM_THREADS; id++) {
    r = pthread_join(threads[id], &status); // obliga threadul specificat sa stea pe procesor pana se termina  

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  return 0;
}

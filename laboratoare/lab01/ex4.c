#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

void *f(void *arg) {
  long id = *(long *)arg;
  printf("Hello World din functia f\n");
  pthread_exit(NULL);
}

void *g(void *arg) {
    long id = *(long *)arg;
    printf("Hello world din functia g\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int r;
  long id;
  void *status;
  long ids[NUM_THREADS];

  ids[0] = 0;
  r = pthread_create(&threads[0], NULL, f, &ids[0]);

  if (r) {
    printf("Eroare la crearea thread-ului 0");
    exit(-1);
  }

  ids[1] = 1;
  r = pthread_create(&threads[1], NULL, g, &ids[1]);

  if (r) {
    printf("Eroare la crearea thread-ului 1");
    exit(-1);
  }

  for (id = 0; id < NUM_THREADS; id++) {
    r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  return 0;
}

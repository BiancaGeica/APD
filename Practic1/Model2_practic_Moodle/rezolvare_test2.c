#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

int *v; // vectorul
int N; // numarul de elemente

pthread_barrier_t barrier;

void *f(void *arg) {
  long id = *(long *)arg;
  int min = v[0];
  int max = v[0];
  int sum = 0;
  int prod = 1;

  switch(id) {
    case 0: 
        for(int i = 1; i < N; i++) {
            if (v[i] < min) {
                min = v[i];
            }
        }

        //printf("minim = %d\n", min);
        break;

    case 1:
        for(int i = 1; i < N; i++) {
            if (v[i] > max) {
                max = v[i];
            }
        }

        //printf("maxim = %d\n", max);
        break;

    case 2:
        for(int i = 0; i < N; i++) {
            sum += v[i];
        }

        //printf("suma = %d\n", sum);
        break;

    case 3:
        for (int i = 0; i < N; i++) {
            prod *= v[i];
            prod %= 1337;
        }

        //printf("produs = %d\n", prod % 1337);
        break;

    default:
        printf("De unde a aparut threadul 5?!\n");
        exit(-1);
  }

  if (id == 0) {
    printf("minim = %d\n", min);
  }

  pthread_barrier_wait(&barrier);
  if (id == 1) {
    printf("maxim = %d\n", max);
  }

  pthread_barrier_wait(&barrier);
  if (id == 2) {
    printf("suma = %d\n", sum);
  }

  pthread_barrier_wait(&barrier);
  if (id == 3) {
    printf("produs = %d\n", prod);
  }

  // pthread_barrier_wait(&barrier);

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int r;
  long id;
  void *status;
  long ids[NUM_THREADS];

  if (argc < 2) {
    fprintf(stderr, "Specificati dimensiunea array-ului\n");
    exit(-1);
  }

  N = atoi(argv[1]);

  srand(5);

  v = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    v[i] = rand() % 100;
  }

/*   for (int i = 0; i < N; i++) {
    printf("%d ", v[i]);
  }
  printf("\n"); */

  r = pthread_barrier_init(&barrier, NULL, 4);
  if (r) {
    printf("Problema la initializarea barierei\n");
    exit(-1);
  }

  for (id = 0; id < NUM_THREADS; id++) {
    ids[id] = id;
    r = pthread_create(&threads[id], NULL, f, &ids[id]);

    if (r) {
      printf("Eroare la crearea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  for (id = 0; id < NUM_THREADS; id++) {
    r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  pthread_barrier_destroy(&barrier);
  free(v);

  return 0;
}

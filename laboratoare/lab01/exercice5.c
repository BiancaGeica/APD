#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/*
    schelet pentru exercitiul 5 - paralelizat
*/

int *arr;
int array_size;
int num_threads;

// Funcția executată de fiecare thread
void *thread_function(void *arg) {
  long id = *(long *)arg;

  // Calculăm start și end pe baza ID-ului
  int start = id * (double) array_size / num_threads;
  int end = MIN((id + 1) * (double) array_size / num_threads, array_size);

  // Incrementăm doar porțiunea atribuită acestui thread
  for (int i = start; i < end; i++) {
    arr[i] += 100;
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }

  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = i;
  }

  // Afișăm vectorul inițial
  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  pthread_t threads[num_threads];
  long ids[num_threads];
  int r;

  // Crearea thread-urilor
  for (long id = 0; id < num_threads; id++) {
    ids[id] = id;
    r = pthread_create(&threads[id], NULL, thread_function, &ids[id]);

    if (r) {
      printf("Eroare la crearea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  // Așteptarea finalizării tuturor thread-urilor
  for (long id = 0; id < num_threads; id++) {
    r = pthread_join(threads[id], NULL);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  // Afișăm vectorul modificat
  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  free(arr);

  return 0;
}
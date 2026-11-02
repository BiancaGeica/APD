#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *arr;
int N;
int P;

int *values;

pthread_barrier_t barrier;

void *f(void *arg) {
  long id = *(long *)arg;

  int sum = 0;
  int prod = 1;
  int min = arr[0];
  int max = arr[0];
  int avg = 0;
  
  switch(id) {
    case 0:
        for(int i = 0; i < N; i++) {
            sum += arr[i];
        }
        values[id] = sum;
        break;

    case 1:
        for (int i = 0; i < N; i++) {
            prod *= arr[i];
        }
        values[id] = prod;
        break;

    case 2:
        for (int i = 1; i < N; i++) {
            if(arr[i] < min) {
                min = arr[i];
            }
        }
        values[id] = min;
        break;

    case 3:
        for (int i = 1; i < N; i++) {
            if(arr[i] > max) {
                max = arr[i];
            }
        }
        values[id] = max;
        break;

    case 4:
        for (int i = 0; i < N; i++) {
            sum += arr[i];
        }
        avg = sum / N;
        values[id] = avg;
        break;

    default:
        printf("De unde a aparut threadul 5?!\n");
        break;
  }

  pthread_barrier_wait(&barrier);

  if (id == 0) {
    for (int i = 0; i < P; i++) {
        switch(i) {
            case 0:
                printf("sum: %d\n", values[i]);
                break;

            case 1:
                printf("prod: %d\n", values[i]);
                break;

            case 2:
                printf("min: %d\n", values[i]);
                break;

            case 3:
                printf("max: %d\n", values[i]);
                break;

            case 4:
                printf("avg: %d\n", values[i]);
                break;

            default:
                printf("Thread 5....again?!\n");
        }
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }

  N = atoi(argv[1]);
  P = atoi(argv[2]);

  arr = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    arr[i] = atoi(argv[i + 3]);
  }

  values = malloc(P * sizeof(int));

  pthread_t threads[P];
  int r;
  long id;
  void *status;
  long ids[P];

  r = pthread_barrier_init(&barrier, NULL, P);
  if (r) {
    printf("Eroare la initializarea barierei\n");
    exit(-1);
  }

  for (id = 0; id < P; id++) {
    ids[id] = id;
    r = pthread_create(&threads[id], NULL, f, &ids[id]);

    if (r) {
      printf("Eroare la crearea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  for (id = 0; id < P; id++) {
    r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  pthread_barrier_destroy(&barrier);
  free(arr);
  free(values);

  return 0;
}

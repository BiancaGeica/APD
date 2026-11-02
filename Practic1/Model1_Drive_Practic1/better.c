#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int *arr;
int array_size;
int num_threads;
int value;
int *sum;
int *ap;

pthread_barrier_t barrier;

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    int sum_local = 0;
    int ap_local = 0;

    int start = thread_id * (double) array_size / num_threads;
    int end = MIN((thread_id + 1) * (double) array_size / num_threads, array_size);
    for (int i = start; i < end; i++) {
      if (arr[i] == value) {
        // printf("sum = %d, ap = %d, i = %d\n", sum[i], ap[i], i); OK
        sum_local += i;
        ap_local++;
        // printf("sum = %d, ap = %d, i = %d\n", sum[i], ap[i], i); // OK
      }
    }

    sum[thread_id] = sum_local;
    ap[thread_id] = ap_local;

    pthread_barrier_wait(&barrier);

    int sum_totala = 0;
    int ap_totale = 0;
    if (thread_id == 0) {
      for (int i = 0; i < num_threads; i++) {
        // printf("sum_totala = %d, ap_totale = %d, i = %d\n", sum_totala, ap_totale, i);
        // printf("sum = %d, ap = %d, i = %d\n", sum[i], ap[i], i);
        sum_totala += sum[i];
        ap_totale += ap[i];
        // printf("sum_totala = %d, ap_totale = %d, i = %d\n", sum_totala, ap_totale, i);
        // printf("sum = %d, ap = %d, i = %d\n", sum[i], ap[i], i);
      }

      printf("%d %d\n", ap_totale, sum_totala);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Specificati dimensiunea array-ului, numarul de thread-uri si valoarea cautata\n");
    exit(-1);
  }

  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);
  value = atoi(argv[3]);

  // printf("%d, %d, %d\n", array_size, num_threads, value);

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = (i + 3) % 5;
  }

  sum = malloc(num_threads * sizeof(int));
  ap = malloc(num_threads * sizeof(int));

  pthread_t tid[num_threads];
	int thread_id[num_threads];

  pthread_barrier_init(&barrier, NULL, num_threads);

	for (int i = 0; i < num_threads; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}

  /* for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  } */

  pthread_barrier_destroy(&barrier);

  free(arr);
  free(sum);
  free(ap);

  return 0;
}
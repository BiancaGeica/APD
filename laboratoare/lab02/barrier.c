#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

pthread_barrier_t barrier;


// TODO: de folosit bariera in aceasta functie
void *f(void *arg)
{
	int thread_id = *(int *)arg;

	if (thread_id == 1) {
		printf("1\n");
	}

	pthread_barrier_wait(&barrier);
	if (thread_id == 0) {
		printf("2\n");
	}

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	int i, r;
	void *status;
	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];

	int check_create;
	check_create = pthread_barrier_init(&barrier, NULL, 2);
	if (check_create) {
		printf("Eroare la crearea barierei\n");
		exit(-1);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		arguments[i] = i;
		r = pthread_create(&threads[i], NULL, f, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	int check_destroy = pthread_barrier_destroy(&barrier);
	if (check_destroy) {
		printf("Eroare la distrugerea barierei\n");
		exit(-1);
	}

	return 0;
}

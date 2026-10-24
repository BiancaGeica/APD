#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

// problema la acest exercitiu este faptul ca threadurile nu se executa in ordine crescatoare, ele sunt random, deci nu avem
// sub nicio forma garantia ca primul thread care executa functia este chiar threadul 0, deci in cazul (foarte des intalnit)
// in care intra intai al doilea thread, se va afisa intai al doilea mesaj, apoi primul

// pentru a rezolva aceasta problema, nu lasam al doilea thread sa ajunga la conditia dedicata lui pana nu a ajuns primul thread
// la conditia specifica lui, deci in acest caz folosim o bariera

// pas 1: se declara global bariera
pthread_barrier_t barrier;

// TODO: de folosit bariera in aceasta functie
void *f(void *arg)
{
	int thread_id = *(int *)arg;

	if (thread_id == 1) {
		printf("1\n");
	}

    // pas 3: se adauga bariera in zona unde este necesara
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

    // pas 2: se initializeaza bariera, iar ca numar de threaduri, ii dam NUM_THREADS
    r = pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    if (r) {
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

    // pas 4: dupa ce am terminat, ca si la pointeri, distrugem bariera
    pthread_barrier_destroy(&barrier);

	return 0;
}

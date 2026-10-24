#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 // am modificat din 2 in 5 sa imi confirm ipoteza ca rezultatul ajunge 10

// de ce vrem sa adaugam mutex? -> deoarece adunarea nu este operatie atomica, mai multe threaduri pot incerca sa rescrie 
// variabila a si astfel, in loc sa primim rezultatul asteptat, 4, putem vedea si rezultatul 2 uneori, ceea ce nu e ok

// solutie: adaugarea unui mutex
// unde? -> acolo unde este zona critica, adica in jurul adunarii


// pas1: se declara global mutexul
pthread_mutex_t mutex;

int a = 0;

// TODO: adaugati mutexul in functia de mai jos
void *f(void *arg)
{
    // pas 3: se pune mutex-ul in zona critica
    pthread_mutex_lock(&mutex);
	a += 2;
    pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i, r;
	void *status;
	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];

    // pas 2: Se initializeaza mutexul
    r = pthread_mutex_init(&mutex, NULL);
    if (r) {
        printf("Eroare la creearea mutexului");
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

    // NU ESTE OK SA SE INITIALIZEZE DUPA CREEAREA THREADURILOR PT CA ATUNCI CAND UN THREAD ISI INCEPE EXECUTIA, VA DA DE MUTEX-UL
    // CARE INCA NU A FOST INITIALIZAT SI ASTFEL SE AJUNGE LA COMPORTAMENT NEDETERMINIST
    /* // pas 2: Se initializeaza mutexul
    r = pthread_mutex_init(&mutex, NULL);
    if (r) {
        printf("Eroare la creearea mutexului");
        exit(-1);
    } */
    

	for (i = 0; i < NUM_THREADS; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

    // pas 4: ca si la lucrul cu pointerii: se elibereaza memoria dupa ce am folosit
    pthread_mutex_destroy(&mutex);

	printf("a = %d\n", a);

	return 0;
}

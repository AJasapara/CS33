#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;

void* thread (void* vargp) {
	int id = *(int*)vargp;
	if (n >= id) {
		pthread_t baby [2];
		int baby1 = 2*id + 1;
		int baby2 = 2*id + 2;
		pthread_create(baby, NULL, thread, &baby1);
		pthread_create(baby+1, NULL, thread, &baby2);
		pthread_join(baby[0], NULL);
		pthread_join(baby[1], NULL);
		printf("Thread %d done\n", id);
	}
}

int main (int argc, char** argv) {
	n = atoi (argv [1]);
	if (n < 1) n = 1;
	n = (1 << n) - 2;
	int first = 0;
	thread(&first);
	return 0;
}
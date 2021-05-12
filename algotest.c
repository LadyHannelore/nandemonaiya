#include "algotest.h"
#include "lib/algorithms.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#define NANOSEC_PER_SEC 1E9

#define TIMER_START clockid_t c_id = 0;\
					struct timespec t_start, t_end;\
					clock_gettime(c_id, &t_start);

#define RETURN_TIME clock_gettime(c_id, &t_end);\
					return ( t_end.tv_sec - t_start.tv_sec ) + ( t_end.tv_nsec - t_start.tv_nsec ) / NANOSEC_PER_SEC;




void* levenshtein_worker(void* arg){
	char** cases = (char**) arg;
	d_levenshtein(cases[0], cases[1], strlen(cases[0]), strlen(cases[1]));
	pthread_exit(NULL);
}

void* worker(void* arg){
	int n = *(int *)arg;	

}

double levenshtein_fork(int n, int processes){
	char* test_cases[] = {"France", "French", "Bread", "Broad"};
	int c = 0;
	TIMER_START
	for(int i=0; i<processes; i++){
		pid_t pid;
		pid = fork();
		if(pid == 0){
			char* case1 = test_cases[c%n], *case2 = test_cases[c%n + 1];
			d_levenshtein(case1, case2, strlen(case1), strlen(case2));
			c += 2;
			exit(1);
		}
	}
	wait(NULL);
	RETURN_TIME
}

double levenshtein_thread(int n, const int threads) {
	char* test_cases[] = {"France", "French", "Bread", "Broad"};
	int c = 0;
	pthread_t tid[threads];
	TIMER_START
	for(int i=0; i<threads; i++){
		char* cases[] = {test_cases[c%n], test_cases[c%n + 1]};
		c += 2;
		pthread_create(&tid[i], NULL, levenshtein_worker, (void *) cases);
	}

	for(int i=0; i<threads; i++){
		pthread_join(tid[i], NULL);
	}
	RETURN_TIME
}
	static double *result;

double cat_fork(int n, const int processes) {
	TIMER_START
	int chunk_size = n/processes;
	int lower, upper = 2;
	result = mmap(NULL, sizeof(result), PROT_READ | PROT_WRITE,
					MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(result == NULL)
		perror("mmap");

	*result = 1;
	for (size_t i = 0; i < processes; i++) {
		pid_t pid;
		lower = upper;
		upper += chunk_size;
		upper = (n+1 < upper) ? n+1 : upper;

		pid = fork();
		if(pid == 0){
			double r = 1;
			for(int k = lower; k < upper; k++){
				r *= (n+k);
				r /= k;
			}
			*result *= r;
			exit(1);
		}
	}
	for(int i=0; i< processes; i++)
		wait(NULL);
	munmap(result, sizeof(double));
	RETURN_TIME
}

void *catalan_worker(void *argv){
	int *args = (int *)argv;
	double *r = malloc(sizeof(double));
	*r = 1;

	for(int k = args[0]; k < args[1]; k++){
		*r *= (args[2]+k);
		*r /= k;
	}
	pthread_exit(r);
}

double cat_thread(int n, const int threads) {
	TIMER_START
	pthread_t tid[threads];
	int chunk_size = n/threads;
	int lower, upper = 2;
	double result = 1;

	for (size_t i = 0; i < threads; i++) {
		lower = upper;
		upper += chunk_size;
		upper = (n+1 < upper) ? n+1 : upper;
		int* argv = calloc(3, sizeof(int));
		argv[0] = lower;
		argv[1] = upper;
		argv[2] = n;
		pthread_create(&tid[i], NULL, catalan_worker, (void *)argv);

	}
	for(int i=0; i< threads; i++){
		double *r;
		pthread_join(tid[i], (void **)&r);
		result *= *r;
	}
	// printf("%lf\n", result);

	RETURN_TIME
}
int lazy_fork(int n, const int processes) {
	TIMER_START
	for (size_t i = 0; i < processes; i++) {
		pid_t pid;
		pid = fork();
		if(pid == 0){

			exit(1);
		}
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}

int trig_fork(int n, const int processes) {
	TIMER_START
	for (size_t i = 0; i < processes; i++) {
		pid_t pid;
		pid = fork();
		if(pid == 0){

			exit(1);
		}
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}

int taylor_fork(int x, const int processes) {
	TIMER_START
	for (size_t i = 0; i < processes; i++) {
		pid_t pid;
		pid = fork();
		if(pid == 0){

			exit(1);
		}
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}

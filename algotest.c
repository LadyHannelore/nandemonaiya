#include "algotest.h"
#include "lib/algorithms.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define NANOSEC_PER_SEC 1E9

#define TIMER_START clockid_t c_id = 0;\
					struct timespec t_start, t_end;\
					clock_gettime(c_id, &t_start);

#define RETURN_TIME clock_gettime(c_id, &t_end);\
					return ( t_end.tv_sec - t_start.tv_sec ) + ( t_end.tv_nsec - t_start.tv_nsec ) / NANOSEC_PER_SEC;


typedef struct test_args {
	int n;
	int (*func)(int, int);
	char** arg_list;
}test_args;


void* levenshtein_worker(void* arg){
	char** cases = (char**) arg;
	d_levenshtein(cases[0], cases[1], strlen(cases[0]), strlen(cases[1]));
	pthread_exit(NULL);
}

void* worker(void* func){

}

double levenshtein_fork(int processes){
	char* test_cases[] = {"France", "French", "Bread", "Broad"};
	int n = 4;
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

double levenshtein_thread(const int threads) {
	char* test_cases[] = {"France", "French", "Bread", "Broad"};
	int n = 4;
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


int cat_fork(int n, int processes) {
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

int lazy_fork(int n, int processes) {
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

int trig_fork(int n, int processes) {
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

int taylor_fork(int x, int processes) {
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

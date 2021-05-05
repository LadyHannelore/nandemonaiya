#include "algotest.h"
#include "lib/algorithms.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define NANOSEC_PER_SEC 1E9

#define TIMER_START clockid_t c_id = 0;\
					struct timespec t_start, t_end;\
					clock_gettime(c_id, &t_start);

#define RETURN_TIME clock_gettime(c_id, &t_end);\
					return ( t_end.tv_sec - t_start.tv_sec ) + ( t_end.tv_nsec - t_start.tv_nsec ) / NANOSEC_PER_SEC;


double levenshtein_fork(char* str1, char* str2, int n, int m, int processes){
	TIMER_START
	for(int i=0; i<processes; i++){
		pid_t pid;
		pid = fork();
		if(pid == 0){
			d_levenshtein(str1, str2, n, m);
			exit(1);
		}
	}
	wait(NULL);
	RETURN_TIME
}
int cat_fork()
{
	TIMER_START
	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME

}
int lazy_fork()
{
	TIMER_START
	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}
int trig_fork()
{
	TIMER_START
	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}
int taylor_fork(int abc)
{
	TIMER_START
	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
	wait(NULL);
	RETURN_TIME
}

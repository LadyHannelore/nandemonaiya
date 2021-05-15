#include <stdio.h>
#include "algotest.h"
#include <string.h>

void generate_image(char* title, double* p_data, double* t_data, const int n, char* xlabel) {
	FILE *gp = popen("gnuplot", "w");

	fprintf(gp, "set key noenhanced\n" 
				"set title '%s' noenhanced\n"
				"set style data linespoints\n"
				"set xlabel '%s'\n"
				"set ylabel 'time (ms)'\n"
				"set style line 1 lw 1 lc rgb '#990042' ps 2 pt 7 pi 1\n"
				"set style line 2 lw 1 lc rgb '#2E8B57' ps 2 pt 7 pi 1\n"
				"set terminal png\n"
				"set output '%s.png'\n"
				"plot '-' title 'processes' ls 1, '' title 'threads' ls 2\n", title, xlabel, title);
	for(int i=0; i<n; i++){
		fprintf(gp, "%d %lf\n", i, p_data[i]);
	}
	fprintf(gp, "e\n");
	for(int i=0; i<n; i++){
		fprintf(gp, "%d %lf\n", i, t_data[i]);
	}

	fprintf(gp, "e\n");
	fflush(gp);
	pclose(gp);
}

void test_and_generate(char* title, int n, double (*process)(int, const int), double (*thread)(int, const int), char* xlabel) {
	double fork_times[10] = {0}, thread_times[10] = {0};

	for(int p=1; p<10; p++){
		fork_times[p] = 1000*process(n, p);
		thread_times[p] = 1000*thread(n, p);
	}
	generate_image(title, fork_times, thread_times, 10, xlabel);

}

void taylor_test(){
	double taylor_thread_time[10] = {0}, taylor_fork_time[10] = {0};
	int i = 0;
	for(int i = 1; i<10; i++){
		taylor_fork_time[i] = 1000.0*taylor_fork(i*20);
		taylor_thread_time[i] = 1000.0*taylor_thread(i*20);
	}

	FILE *gp = popen("gnuplot", "w");

	fprintf(gp, "set key noenhanced\n" 
				"set title 'Taylor_Series' noenhanced\n"
				"set style data linespoints\n"
				"set xlabel 'x'\n"
				"set ylabel 'time (ms)'\n"
				"set style line 1 lw 1 lc rgb '#990042' ps 2 pt 7 pi 1\n"
				"set style line 2 lw 1 lc rgb '#2E8B57' ps 2 pt 7 pi 1\n"
				"set terminal png\n"
				"set output 'Taylor_Series.png'\n"
				"plot '-' title 'processes' ls 1, '' title 'threads' ls 2\n");

	for(int i=1; i<=10; i++){
		fprintf(gp, "%d %lf\n", i*20, taylor_fork_time[i-1]);
	}
	fprintf(gp, "e\n");
	for(int i=1; i<10; i++){
		fprintf(gp, "%d %lf\n", i*20, taylor_thread_time[i-1]);
	}

	fprintf(gp, "e\n");
	fflush(gp);
	pclose(gp);

}
int main() {
	test_and_generate("Levenshtein_Distance", 4, &levenshtein_fork, &levenshtein_thread, "processes/threads");
	test_and_generate("Catalan_Series_n_500", 500, &cat_fork, &cat_thread, "processes/threads"); 
	taylor_test();

    return 0;
}
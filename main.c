#include <stdio.h>
#include "algotest.h"
#include <string.h>

void generate_image(char* title, double* p_data, double* t_data, const int n) {
	FILE *gp = popen("gnuplot", "w");

	fprintf(gp, "set key noenhanced\n" 
				"set title '%s' noenhanced\n"
				"set style data linespoints\n"
				"set xlabel 'processes/threads'\n"
				"set ylabel 'time'\n"
				"set style line 1 lw 1 lc rgb '#990042' ps 2 pt 7 pi 1\n"
				"set style line 2 lw 1 lc rgb '#2E8B57' ps 2 pt 7 pi 1\n"
				"set terminal png\n"
				"set output '%s.png'\n"
				"plot '-' title 'processes' ls 1, '' title 'threads' ls 2\n", title, title);
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

void test_and_generate(char* title, int n, double (*process)(int, const int), double (*thread)(int, const int)) {
	double fork_times[10] = {0}, thread_times[10] = {0};

	for(int p=0; p<10; p++){
		fork_times[p] = process(n, p);
		thread_times[p] = thread(n, p);
	}
	generate_image(title, fork_times, thread_times, 10);

}
int main() {
	test_and_generate("Levenshtein_Distance", 4, &levenshtein_fork, &levenshtein_thread);
    return 0;
}
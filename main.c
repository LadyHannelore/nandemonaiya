#include <stdio.h>
#include "algotest.h"
#include <string.h>

void generate_image(char* title, char* x, char* y, double* data, const int n) {
	FILE *gp = popen("gnuplot", "w");

	fprintf(gp, "set key noenhanced\n" 
				"set title '%s' noenhanced\n"
				"set style data linespoints\n"
				"set xlabel '%s'\n"
				"set ylabel '%s'\n"
				"set style line 1 lw 1 lc rgb '#990042' ps 2 pt 7 pi 1\n"
				"set terminal png\n"
				"set output '%s.png'\n"
				"plot '-' ls 1\n", title, x, y, title);
	for(int i=0; i<n; i++){
		fprintf(gp, "%d %lf\n", i, data[i]);
	}
	fprintf(gp, "e\n");
	fflush(gp);
	pclose(gp);
}

int main() {
	char* title = "Levenshtein_with_increasing_processes";
	double fork_times[10] = {0}, thread_times[10] = {0};
	char* test[] = {"Bread", "Broad"};	

	for(int p=0; p<10; p++){
		fork_times[p] = levenshtein_fork(test[0], test[1], strlen(test[0]), strlen(test[1]), p);
	}
	generate_image(title, "processes", "time", fork_times, 10);
	
    return 0;
}
#include "damerau-levenshtein.c"
#include <time.h>
#include <unistd.h>
#define NANOSEC_PER_SEC 1E9

int main(){
    
    clockid_t c_id;
    struct timespec t_start, t_end;
    clock_gettime(c_id, &t_start);
  
    int distance = d_levenshtein("France", "French", 6, 6);
    clock_gettime(c_id, &t_end);
    
    double accum = ( t_end.tv_sec - t_start.tv_sec ) + ( t_end.tv_nsec - t_start.tv_nsec ) / NANOSEC_PER_SEC;
    printf("Distance: %d\n", distance);
    printf("Time: %lfs\n", accum);
}
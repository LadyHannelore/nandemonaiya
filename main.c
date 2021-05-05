#include <stdio.h>
#include "algotest.h"


int main(){
	printf("%lf\n", levenshtein_fork("France", "French", 6, 6, 3));
	printf("%lf\n", taylor_fork(4));
	printf("%lf\n", cat_fork());
	printf("%lf\n", trig_fork());
	printf("%lf\n", lazy_fork());
	
    return 0;
}
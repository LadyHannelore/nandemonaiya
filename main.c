#include <stdio.h>
#include "algotest.h"


int main(){
	printf("%lf\n", levenshtein_fork("France", "French", 6, 6, 3));
}
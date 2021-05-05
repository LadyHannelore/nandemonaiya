#include<stdio.h>
#include<math.h>
#define min(x,y) ((x) < (y) ? (x) : (y))
#define min3(a,b,c) ((a)< (b) ? min((a),(c)) : min((b),(c)))


int catalonia()
{
    int catalan[10];
    for (int n = 0; n < 10; n++){
    
 
    catalan[0] = catalan[1] = 1;
 
    // Fill entries in catalan[] using recursive formula
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++)
            catalan[i] += catalan[j] * catalan[i - j - 1];
    }

    }
    
    return catalan[9];
}
int lazy_cater()
{
	double cut;
    int N=10;
    do
    {
        cut = 1+(N*(N+1))/2;
        N--;
    }while(N == 0);

    return N;
}
int triangular_series()
{
    int i, j = 1, k = 1,n=10;
 
    for (i = 1; i <= n; i++) {
        printf(" %d ", k);
        j = j + 1; 
        k = k + j; 
    }
}
int taylor_series(int abc)
{
   
    int x=abc,i;
    int fact = 1,n=10;
    float sum=0;

    
    for(i=1;i<n;i++)
    {
        fact = fact*i;
        sum = sum + (pow(x,i)/fact) ;

    }
    sum= sum +1; //Since series starts with 1

    return sum;
}
int d_levenshtein(char* s, char* t, int n, int m)
{
    int d[n+1][m+1];

    int i;
    int j;
    int l_cost;

    for (i = 0;i <= n;i++)
    {
        d[i][0] = i;
    }
    for(j = 0; j<= m; j++)
    {
        d[0][j] = j;
    }
    for (i = 1;i <= n;i++)
    {
        for(j = 1; j<= m; j++)
        {
            if( s[i-1] == t[j-1] )
            {
                l_cost = 0;
            }
            else
            {
                l_cost = 1;
            }
            d[i][j] = min3(
            d[i-1][j] + 1,                  // delete
            d[i][j-1] + 1,         // insert
            d[i-1][j-1] + l_cost           // substitution
            );
            if( (i > 1) && 
                (j > 1) &&  
                (s[i-1] == t[j-2]) && 
                (s[i-2] == t[j-1])
            ) 
            {
                d[i][j] = min(
                d[i][j],
                d[i-2][j-2] + l_cost   // transposition
                );
            }
        }
    }
    return d[n][m];
}


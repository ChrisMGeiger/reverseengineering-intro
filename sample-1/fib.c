#include <math.h>
#include <stdio.h>

long fibb_recursive(long a, long b, int n)
{
    if (--n > 0) {
        return fibb_recursive(b, a+b, n);
    } else {
        return a;
    }
}

long fibb_iterative(int n)
{
    int fnow = 0, fnext = 1, tempf;
    while(--n>0){
        tempf = fnow + fnext;
        fnow = fnext;
        fnext = tempf;
        }
        return fnext;
}

#define PHI ((1 + sqrt(5))/2)
 
long fibb_analytic(unsigned int n) 
{
    return floor( (pow(PHI, n) - pow(1 - PHI, n))/sqrt(5) );
}

int main(int argc, char *argv[])
{
    unsigned int i;

    for (i=1; i < 10; i++) {
        long recur = fibb_recursive(1, 1, i);
        long iter = fibb_iterative(i);        
        long analytic = fibb_analytic(i); 

        if (recur != iter || iter != analytic) {
            printf("The values have diverged! %ld, %ld, %ld\n", recur, iter, analytic);
        } else {
            printf("%ld ", recur);
        }
    }
}

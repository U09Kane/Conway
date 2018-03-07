#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main () {

    int number = omp_get_max_threads();
    printf("%d\n", number);

    // #pragma omp parallel
    // {
    // int my_rank = omp_get_thread_num();

    // printf("Hello from thread number %d\n", my_rank);
    // }
}

 



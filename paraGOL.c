/*
 Kane Maxcy
 BID: jkmaxcy
 CS 432
 Homework #3
 
 Conway's Game of Life - Parallel Program
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 2

int main(int argc, const char * argv[]) {
    
    // Get input
    // int size = atoi(argv[1]);
    // int max_gens = atoi(argv[2]);
    int size = 100;
    int max_gens = 1000;

    // Time Start
    time_t start;
    time(&start);
    
    // Generate Matrices of N*N   
    int gen[size][size];
    int nextGen[size][size];

    // Intialize each cell with random 1 or 0
    #pragma omp parallel
    {
    int id = omp_get_thread_num();
    int nthreads = omp_get_num_threads();

    for (int row = 0; row < size; row++){
        for (int col = id; col < size; col = col + nthreads){
            gen[row][col] = rand() % 2;
        }
    }

    for (int count = 0; count < max_gens; count++){ // While we haven't reached last generation
        // Analyze each cell
        for (int row = 0; row < size; row++){
            for (int col = id; col < size; col = col + nthreads){
                // Copy cells from current board

                nextGen[row][col] = gen[row][col];
            }
        }
        for (int row = 0; row < size; row++){
            for (int col = id; col < size; col = col + nthreads){
                int neighbors = 0;
                // Get number of neighbors
                for (int y = -1; y < 2; y++){
                    for (int x = -1; x < 2; x++){
                        if (x != 0 && y != 0 && gen[(row + y) % size][(col + x) % size] == 1) {
                            neighbors++;
                        }
                    }
                }
                if (gen[row][col]== 1){ // if Cell is alive...
                    if (neighbors < 2 || neighbors > 3){
                        nextGen[row][col] = 0; // "lonliness"/"overpopulation"
                    } else {
                        nextGen[row][col] = 1; // Survives
                    }
                    
                } else if (*(gen + row*size + col) == 0){ // if Cell is Dead...
                    if (neighbors == 3){
                        nextGen[row][col] = 1; // "Birth"
                    } else {
                        nextGen[row][col] = 0; // Still dead
                    }
                }
            }
        }
        for (int row = 0; row < size; row++){
            for (int col = id; col < size; col = col + nthreads){
                gen[row][col] = nextGen[row][col];
//         printf("%d", gen[row][col]);
            }
//            printf("\n");
        }
//        printf("\n");
    }
    }
    
    // Stop Time
    time_t stop;
    time(&stop);
    printf("Time Taken: %ld seconds\n", stop - start);

    return 0;
}

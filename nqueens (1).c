// Parallelize N queens with pthreads!

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h> // for pthreads


#define N 15 // Board size
#define THREADS 4 // number of threads

int total_solutions = 0;
pthread_mutex_t solution_mutex = PTHREAD_MUTEX_INITIALIZER; // the mutex for updating total_solutions


// check if placing a queen at (row, col) is safe
bool isSafe(int board[], int row, int col) 
{
    for (int i = 0; i < col; i++) {
        if (board[i] == row || abs(board[i] - row) == col - i)
            return false;
    }
    return true;
}

// recursive backtracking 
void solve(int board[], int col) 
{
    if (col == N) {
        pthread_mutex_lock(&solution_mutex); // lock to allow update of total_solutions
        total_solutions++;
        pthread_mutex_unlock(&solution_mutex); // unlock after update
        return;
    }

    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            board[col] = row;
            solve(board, col + 1);
        }
    }
}

void* thread_solve(void* arg)  // each thread will begin solving from a different starting row in the first column
{
    int start_row = *(int*)arg; // the starting row
    int board[N]; // initialize board 

    // initializing board ...
    for (int i = 0; i < N; i++)
        board[i] = -1;

    board[0] = start_row; // places queen at (start_row, 0)
    solve(board, 1); // start solving from column 1
    return NULL;
}

int main() 
{
    pthread_t threads[N]; // one thread
    int start_rows[N]; // the starting rows
    for (int i = 0; i < N; i++) { // for each row in the first column need to create a thread
        start_rows[i] = i;
        pthread_create(&threads[i], NULL, thread_solve, &start_rows[i]); // create the thread
    }
    for (int i = 0; i < N; i++) { // for each thread join it
        pthread_join(threads[i], NULL); // wait for thread to finish
    }

    printf("Total solutions for N=%d: %d\n", N, total_solutions); // print 
    return 0;
}

# Midterm
Task 1: This program focuses on parallelizing the program nqueens using pthreads, generating partial solutions, and assigning each starting row to its own thread
Each thread executes recursive backtracking and updates the shared total_solutions with a mutex. This allows for the logic to remain sequential, but
has some branches in parallel. We also timed this program from sequential - 4 threads to determine the time it took to execute the program.

Task 2: This program focused on implementing a custom reader-writer lock using pthread mutexs and cond variables to let multiple readers proceed at the same time.
While writers get exclusive access, the locks track readers, writers, and waiting writers, then we applied condition signaling to manage fairness and prevent
starvation between the different threads. 

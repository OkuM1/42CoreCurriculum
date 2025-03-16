#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000 // Define a reasonable maximum value for n

int board[MAX_N]; // Fixed-size array to store queen positions
int n;

// Check if placing a queen at (row, col) is safe
int is_safe(int row, int col) {
    int i = 0;
    while (i < col) {
        if (board[i] == row || abs(board[i] - row) == abs(i - col)) {
            return 0; // Not safe
        }
        i++;
    }
    return 1; // Safe
}

// Print the solution in the required format
void print_solution() {
    int i = 0;
    while (i < n) {
        fprintf(stdout, "%d ", board[i]);
        i++;
    }
    fprintf(stdout, "\n");
}

// Recursive function to solve the N-Queens problem
void solve_n_queens(int col) {
    if (col == n) {
        print_solution(); // All queens are placed, print the solution
        return;
    }

    int row = 0;
    while (row < n) {
        if (is_safe(row, col)) {
            board[col] = row; // Place the queen at (row, col)
            solve_n_queens(col + 1); // Move to the next column
        }
        row++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]); // Parse n from command line
    if (n <= 0 || n > MAX_N) {
        fprintf(stderr, "n must be a positive integer and <= %d\n", MAX_N);
        return 1;
    }

    solve_n_queens(0); // Start solving from column 0
    return 0;
}
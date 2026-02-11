#include <iostream>
#include <vector>
#include <random>

using namespace std;


void printBoard(const vector<int> board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || 
            board[i] - i == col - row || 
            board[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

bool placeQueens(vector<int>& board, int row, int n) {
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col; // Place queen
            if (row == n - 1 || placeQueens(board, row + 1, n)) {
                return true; // Move to next row
            }
            board[row] = -1; // Backtrack
        }
    }
    return false; // No valid position found
}

bool solveNQueens(int n) {
    vector<int> board (n, -1); // Initialize the board with -1 (no queen placed)
    srand(time(0)); // Seed the random number generator

    int attempts = 0;
    while(attempts < 500){
        attempts++;
        if(placeQueens(board, 0, n)) {
            printBoard(board);
            return true;
        }
    }
    cout << "No solution found after " << attempts << " attempts." << endl;
    return false;
}



int main() {
    int queens;
    cout << "Enter the number of queens: ";
    cin >> queens;

    if(solveNQueens(queens)){
        cout << "Solution found!" << endl;
    } else {
        cout << "No solution exists for " << queens << " queens." << endl;
    }

    return 0;
}
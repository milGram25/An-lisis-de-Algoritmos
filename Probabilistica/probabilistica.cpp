#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

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

bool placeQueensRandomly(vector<int>& board, int n, mt19937& g) {
    fill(board.begin(), board.end(), -1); // Clear the board for a new try

    for (int row = 0; row < n; row++) {
        vector<int> safeColumns;

        // Find all safe columns for the current row
        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col)) {
                safeColumns.push_back(col);
            }
        }

        // If no safe columns are left, this "try" is a failure
        if (safeColumns.empty()) {
            return false; 
        }

        // Pick one safe column at random
        uniform_int_distribution<int> dist(0, safeColumns.size() - 1);
        board[row] = safeColumns[dist(g)];
    }
    return true; // Successfully placed N queens
}

bool solveNQueens(int n, int maxTries) {
    vector<int> board(n, -1);
    random_device rd;
    mt19937 g(rd());

    int attempts = 0;
    while (attempts < maxTries) {
        attempts++;
        if (placeQueensRandomly(board, n, g)) {
            cout << "Solution found on attempt #" << attempts << "!" << endl;
            printBoard(board);
            return true;
        }
    }

    cout << "Reached limit of " << maxTries << " tries without a solution." << endl;
    return false;
}

int main() {
    int queens, maxTries;
    cout << "Enter the number of queens: ";
    cin >> queens;
    cout << "Enter the maximum number of tries: ";
    cin >> maxTries;

    solveNQueens(queens, maxTries);
    return 0;
}
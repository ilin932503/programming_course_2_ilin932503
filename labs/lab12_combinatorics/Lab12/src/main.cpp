#include <iostream>
#include <vector>
#include <clocale>
using namespace std;

int n;
int P[21], H[21], R[41], L[41];
int solutionNumber = 0;

// СПОСОБ 1: с использованием матрицы

bool isSafeMatrix(const vector<vector<bool>>& board, int row, int col, int size) {
    for (int step = 1; step <= row; ++step) {
        if (board[row - step][col]) return false; //вертикаль
        if (col - step >= 0 && board[row - step][col - step]) return false;
        if (col + step < size && board[row - step][col + step]) return false;
    }
    return true;
}

void printBoardMatrix(const vector<vector<bool>>& board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << (board[i][j] ? "F " : ". ");
        }
        cout << "\n";
    }
    cout << "\n";
}

void solveMatrix(vector<vector<bool>>& board, int row, int size, int& count) {
    if (row == size) {
        count++;
        solutionNumber++;
        cout << "#" << solutionNumber << ":\n";
        printBoardMatrix(board, size);
        return;
    }

    for (int col = 0; col < size; col++) {
        if (isSafeMatrix(board, row, col, size)) {
            board[row][col] = true;
            solveMatrix(board, row + 1, size, count);
            board[row][col] = false;
        }
    }
}

// СПОСОБ 2

void queen(int k, int& count) {
    for (int i = 1; i <= n; i++) {
        if (H[i] == 0 && R[i - k + 21] == 0 && L[i + k] == 0) {
            P[k] = i;
            H[i] = 1;
            R[i - k + 21] = 1;
            L[i + k] = 1;

            if (k == n) {
                count++;
            }
            else {
                queen(k + 1, count);
            }

            H[i] = 0;
            R[i - k + 21] = 0;
            L[i + k] = 0;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "введите количество ферзей: ";
    cin >> n;

    int count1 = 0, count2 = 0;

    // СПОСОБ 2 
    for (int i = 1; i <= n; i++) H[i] = 0;
    for (int i = 2; i <= n + n; i++) {
        R[i] = 0;
        L[i] = 0;
    }
    queen(1, count2);
    cout << count2 << "\n\n";

    // СПОСОБ 1 - выводим доски
    solutionNumber = 0;
    vector<vector<bool>> board(n, vector<bool>(n, false));
    solveMatrix(board, 0, n, count1);

    return 0;
}
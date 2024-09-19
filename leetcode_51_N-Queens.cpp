/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addSolution(char*** result, int* returnSize, int** returnColumnSizes, char** board, int n) {
    result[*returnSize] = (char**)malloc(n * sizeof(char*));
    (*returnColumnSizes)[*returnSize] = n;
    for (int i = 0; i < n; i++) {
        result[*returnSize][i] = strdup(board[i]);
    }
    (*returnSize)++;
}

int isValid(char** board, int row, int col, int n) {
    // ���ͬһ���Ƿ��лʺ�
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') {
            return 0;
        }
    }

    // ������ϵ����µĶԽ���
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return 0;
        }
    }

    // ������ϵ����µķ��Խ���
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return 0;
        }
    }

    return 1;
}

void solve(char*** result, int* returnSize, int** returnColumnSizes, char** board, int row, int n) {
    if (row == n) {
        addSolution(result, returnSize, returnColumnSizes, board, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isValid(board, row, col, n)) {
            board[row][col] = 'Q';  // ���ûʺ�
            solve(result, returnSize, returnColumnSizes, board, row + 1, n);
            board[row][col] = '.';  // ���ݣ��Ƴ��ʺ�
        }
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int maxSolutions = 1;
    for (int i = 1; i <= n; i++) {
        maxSolutions *= i;
    }

    char*** result = (char***)malloc(maxSolutions * sizeof(char**));
    *returnColumnSizes = (int*)malloc(maxSolutions * sizeof(int));

    // ��ʼ������
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc((n + 1) * sizeof(char));
        memset(board[i], '.', n);
        board[i][n] = '\0';  // ������
    }

    solve(result, returnSize, returnColumnSizes, board, 0, n);

    // �ͷ���ʱ���̵��ڴ�
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    return result;
}


#include <stdbool.h>

void solve(int n, int row, int cols, int diagonals1, int diagonals2, int* count) {
    if (row == n) {
        (*count)++;
        return;
    }

    int available_positions = (~(cols | diagonals1 | diagonals2)) & ((1 << n) - 1);

    while (available_positions) {
        int position = available_positions & -available_positions;
        available_positions &= (available_positions - 1);  // 移除最低位的 1

        solve(n, row + 1, cols | position, (diagonals1 | position) << 1, (diagonals2 | position) >> 1, count);
    }
}

int totalNQueens(int n) {
    if (n == 1) {
        return 1;
    }

    if (n < 1) {
        return 0;
    }

    int count = 0;

    // 处理对称性优化
    int mid = n / 2;
    for (int i = 0; i < mid; i++) {
        int position = 1 << i;
        solve(n, 1, position, position << 1, position >> 1, &count);
    }

    count *= 2; // 对称性翻倍

    // 如果 n 是奇数，处理中间列的特殊情况
    if (n % 2 == 1) {
        int position = 1 << mid;
        solve(n, 1, position, position << 1, position >> 1, &count);
    }

    return count;
}

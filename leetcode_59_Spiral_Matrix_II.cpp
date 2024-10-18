/*
给你一个正整数n，生成一个包含1到n^2所有元素，且元素按顺时针顺序螺旋排列的n x n正方形矩阵matrix。

示例 1：

输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]

示例 2：

输入：n = 1
输出：[[1]]



提示：

    1 <= n <= 20

*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int count = 1;
    int** result = (int**)malloc(sizeof(int*)* n);

    for (int i = 0; i < n; i++)
    {
        result[i] = (int*)malloc(sizeof(int) * n);

    }
    while (left <= right && top <= bottom) {

        for (int i = left; i <= right; i++) {
            result[top][i] = count;
            count++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            result[i][right] = count;
            count++;
        }
        right--;

        if (top <= bottom) {

            for (int i = right; i >= left; i--) {
                result[bottom][i] = count;
                count++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
            {
                result[i][left] = count;
                count++;
            }
            left++;
        }
    }

    // 返回列大小信息
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
    }

    // 设置返回的矩阵大小
    *returnSize = n;

    return result;
}
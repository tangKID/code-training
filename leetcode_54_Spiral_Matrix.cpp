/*
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。



示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例 2：

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]



提示：

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

    遍历顺序为：左上 -> 右上 -> 右下 -> 左下 -> 左上，然后内层重复上述遍历顺序
*/
#include <stdlib.h>
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    *returnSize = 0;
    if (matrixSize == 0 || matrixColSize[0] == 0) return NULL;
    int top = 0;  //从0开始，指向 matrix 的第一行。
    int bottom = matrixSize - 1; //从 m-1 开始，指向 matrix 的最后一行。
    int left = 0;  //从0开始，指向 matrix 的第一列。
    int right = matrixColSize[0]-1; //从 n-1 开始，指向matix 的最后一列。
    int totalElements = matrixSize * matrixColSize[0];  // 矩阵中的总元素数
    int* result = (int*)malloc(totalElements * sizeof(int));
    
    while(top <= bottom && left <= right) {
        
        for (int i = left; i <= right; i++)
        {
            // 从左往右遍历top行
            result[(*returnSize)++] = matrix[top][i];
        }
        top++; //遍历完top行后，top++

        for (int i = top; i <= bottom; i++) {
            // 从上到下遍历right列
            result[(*returnSize)++] = matrix[i][right];
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                //从右到左遍历bottom行
                result[(*returnSize)++] = matrix[bottom][i];
            }
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--){
                //从下到上遍历left列
                result[(*returnSize)++] = matrix[i][left];
            }
            left++;
        }
    }
    return result;
}
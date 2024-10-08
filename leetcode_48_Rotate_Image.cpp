/*
48. 旋转图像

给定一个 n × n 的二维矩阵表示一个图像。

将图像顺时针旋转 90 度。
说明：

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
示例 1:

    给定 matrix =
    [
        [1,2,3],
        [4,5,6],
        [7,8,9]
    ],

    原地旋转输入矩阵，使其变为:
    [
        [7,4,1],
        [8,5,2],
        [9,6,3]
    ]

示例 2:

    给定 matrix =
    [
        [ 5, 1, 9,11],
        [ 2, 4, 8,10],
        [13, 3, 6, 7],
        [15,14,12,16]
    ],

    原地旋转输入矩阵，使其变为:
    [
        [15,13, 2, 5],
        [14, 3, 4, 1],
        [12, 6, 8, 9],
        [16, 7,10,11]
    ]
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    
    
    for (int i = 0; i < matrixSize / 2; i++)
    {
        int start = i; // 当前环的起始下标（横纵均相等）
        int end = matrixSize - i - 1; // 当前环的终点下标（横纵均相等）
        for (int j = 0; j < end - start; j++) {
            int temp = matrix[start][start + j];
            matrix[start][start + j] = matrix[end - j][start];
            matrix[end - j][start] = matrix[end][end - j];
            matrix[end][end - j] = matrix[start + j][end];
            matrix[start + j][end] = temp;
        }
    }
}
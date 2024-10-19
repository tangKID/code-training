/*
1. 题目描述

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

说明：m 和 n 的值均不超过 100。

示例 1:

输入: [ [0,0,0], [0,1,0], [0,0,0] ]
输出: 2
解释: 3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：

    向右 -> 向右 -> 向下 -> 向下
    向下 -> 向下 -> 向右 -> 向右
*/
#include <stdio.h>
#include <stdlib.h>

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    int m = obstacleGridSize;
    int n = *obstacleGridColSize;

    // 动态分配dp数组，大小为列数n
    int* dp = (int*)malloc(sizeof(int) * n);

    // 初始化dp数组，处理第一列是否有障碍物
    dp[0] = (obstacleGrid[0][0] == 1) ? 0 : 1;

    // 初始化第一行的dp值，障碍物之后的路径数为0
    for (int j = 1; j < n; j++) {
        dp[j] = (obstacleGrid[0][j] == 1 || dp[j - 1] == 0) ? 0 : 1;
    }

    // 填充dp数组
    for (int i = 1; i < m; i++) {
        // 处理第一列（第一列只能由上面下来）
        dp[0] = (obstacleGrid[i][0] == 1) ? 0 : dp[0];

        for (int j = 1; j < n; j++) {
            // 如果有障碍物，dp[j]为0；否则更新dp[j]
            if (obstacleGrid[i][j] == 1) {
                dp[j] = 0;
            }
            else {
                dp[j] += dp[j - 1];  // dp[j] = 上方的值 + 左方的值
            }
        }
    }

    int result = dp[n - 1];  // 右下角的值就是结果
    free(dp);  // 释放动态分配的内存
    return result;
}
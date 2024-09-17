/*
1. 题目描述

给定一个没有重复数字的序列，返回其所有可能的全排列。

示例:

    输入: [1,2,3]
    输出:
    [
    [1,2,3],
    [1,3,2],
    [2,1,3],
    [2,3,1],
    [3,1,2],
    [3,2,1]
    ]
*/
#include <stdio.h>
#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void dfs(int* nums, int numsSize, int** result, int* returnSize, int start) {
    if (start == numsSize) {

        result[*returnSize] = (int*)malloc(numsSize * sizeof(int));

        for (int i = 0; i < numsSize; i++)
        {
            result[*returnSize][i] = nums[i];
        }
        (*returnSize)++;
        return;
    }
    for (int i = 0; i < numsSize; i++)
    {
        swap(nums, start, i);  // 交换当前元素与start位置 
        dfs(nums, numsSize, result, returnSize, start + 1); // 递归处理后续元素
        swap(nums, start, i); // 回溯，恢复原数组

    }

}


void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}


int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    //计算全排列的数量为numsSize!
    int totalPermutations = 1;
    for (int i = 2; i <= numsSize; i++)
    {
        totalPermutations *= i;
    }
    // 分配存储结果的空间
    int** result = (int**)malloc(totalPermutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));

    // 深度优先搜索生成全排列
    dfs(nums, numsSize, result, returnSize, 0);

    // 设置每个排列的列大小
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    return result;

}

// 打印二维数组
void printPermutations(int** permutations, int returnSize, int numsSize) {
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            printf("%d ", permutations[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nums[] = { 1, 2, 3 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;
    int** permutations = permute(nums, numsSize, &returnSize, &returnColumnSizes);

    // 打印生成的全排列
    printPermutations(permutations, returnSize, numsSize);

    // 释放内存
    for (int i = 0; i < returnSize; i++) {
        free(permutations[i]);
    }
    free(permutations);
    free(returnColumnSizes);

    return 0;
}

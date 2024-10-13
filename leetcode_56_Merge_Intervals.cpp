/*
1. 题目描述

给出一个区间的集合，请合并所有重叠的区间。

示例 1:

    输入: [[1,3],[2,6],[8,10],[15,18]]
    输出: [[1,6],[8,10],[15,18]]
    解释: 区间[1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2:

    输入: [[1,4],[4,5]]
    输出: [[1,5]]
    解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int compare(const void* a, const void* b) {
    // 用于 qsort 的比较函数，按区间的起始位置升序排序
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    return intervalA[0] - intervalB[0];
}


int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    //先对intervals按起始位置排序
    qsort(intervals, intervalsSize, sizeof(int*), compare);

    int** result = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int*));

    //用于存储合并后的区间个数
    int mergedCount = 0;
    // 初始化第一个区间
    result[mergedCount] = (int*)malloc(2 * sizeof(int));
    result[mergedCount][0] = intervals[0][0];
    result[mergedCount][1] = intervals[0][1];
    (*returnColumnSizes)[mergedCount] = 2;
    mergedCount++;

    // 遍历所有区间进行合并
    for (int i = 1; i < intervalsSize; i++) {
        int* currentInterval = intervals[i];
        int* lastMergedInterval = result[mergedCount - 1];

        // 如果当前区间与上一个合并区间重叠，更新结束位置
        if (currentInterval[0] <= lastMergedInterval[1]) {
            lastMergedInterval[1] = (lastMergedInterval[1] > currentInterval[1]) ? lastMergedInterval[1] : currentInterval[1];
        }
        else {
            // 如果没有重叠，直接添加当前区间
            result[mergedCount] = (int*)malloc(2 * sizeof(int));
            result[mergedCount][0] = currentInterval[0];
            result[mergedCount][1] = currentInterval[1];
            (*returnColumnSizes)[mergedCount] = 2;
            mergedCount++;
        }
    }
    // 设置返回值
    *returnSize = mergedCount;
    return result;
}
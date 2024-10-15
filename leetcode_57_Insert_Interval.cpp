/*
在给定的非重叠区间列表中插入一个新的区间，并在插入后保持这些区间非重叠。如果新的区间与现有区间重叠，我们需要将重叠的区间合并。

解题思路：
步骤：
初始化：

创建一个新数组 result 用来存储合并后的区间。
维护一个新的区间 mergedInterval，在合适的位置合并新的区间。
遍历原始区间数组：

对于每一个区间，如果：
当前区间在 newInterval 之前：直接将其加入 result。
当前区间在 newInterval 之后：如果 newInterval 尚未插入，将 newInterval 合并到 result 中，再加入当前区间。
当前区间与 newInterval 重叠：更新 newInterval 的范围，即将 newInterval 与当前区间合并。
检查 newInterval 是否已插入：

遍历完成后，如果 newInterval 还未被插入，需要手动插入。
内存分配：

因为函数要求返回的数组和列大小数组都需要动态分配，因此需要使用 malloc 分配内存，并在返回时正确设置。
*/

#include <stdlib.h>

// Helper function to get the maximum of two integers
int max(int a, int b) {
    return a > b ? a : b;
}

// Helper function to get the minimum of two integers
int min(int a, int b) {
    return a < b ? a : b;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    // Allocate memory for result array and the column sizes array
    int** result = (int**)malloc((intervalsSize + 1) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((intervalsSize + 1) * sizeof(int));

    int idx = 0; // Result array index
    int i = 0;   // Original intervals array index

    // Add all intervals that end before the new interval starts
    while (i < intervalsSize && intervals[i][1] < newInterval[0]) {
        result[idx] = (int*)malloc(2 * sizeof(int));
        result[idx][0] = intervals[i][0];
        result[idx][1] = intervals[i][1];
        (*returnColumnSizes)[idx] = 2;
        idx++;
        i++;
    }

    // Merge all overlapping intervals with the new interval
    while (i < intervalsSize && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }

    // Add the merged new interval
    result[idx] = (int*)malloc(2 * sizeof(int));
    result[idx][0] = newInterval[0];
    result[idx][1] = newInterval[1];
    (*returnColumnSizes)[idx] = 2;
    idx++;

    // Add the rest of the intervals that start after the new interval
    while (i < intervalsSize) {
        result[idx] = (int*)malloc(2 * sizeof(int));
        result[idx][0] = intervals[i][0];
        result[idx][1] = intervals[i][1];
        (*returnColumnSizes)[idx] = 2;
        idx++;
        i++;
    }

    // Set the return size
    *returnSize = idx;

    return result;
}

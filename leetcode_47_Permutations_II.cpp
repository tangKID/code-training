#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 交换数组中的两个元素
void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

// 比较函数，用于qsort进行排序
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 深度优先搜索递归函数，生成全排列，避免重复
void dfs(int* nums, int numsSize, int** result, int* returnSize, int* temp, int* used, int depth) {
    if (depth == numsSize) {
        // 当到达递归深度等于数组长度时，生成一个新的排列
        result[*returnSize] = (int*)malloc(numsSize * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            result[*returnSize][i] = temp[i];
        }
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        // 如果该元素已经被使用，跳过
        if (used[i]) continue;
        // 剪枝，避免重复排列
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

        // 标记元素被使用
        used[i] = 1;
        temp[depth] = nums[i];
        dfs(nums, numsSize, result, returnSize, temp, used, depth + 1);
        // 回溯，恢复状态
        used[i] = 0;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    // 计算全排列的数量为 numsSize!
    int totalPermutations = 1;
    for (int i = 2; i <= numsSize; i++) {
        totalPermutations *= i;
    }

    // 分配存储结果的空间
    int** result = (int**)malloc(totalPermutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));

    // 排序数组以方便识别重复元素
    qsort(nums, numsSize, sizeof(int), compare);

    // 初始化用于存储当前排列的临时数组
    int* temp = (int*)malloc(numsSize * sizeof(int));
    // 初始化用于判断元素是否被使用的数组
    int* used = (int*)calloc(numsSize, sizeof(int));

    // 深度优先搜索生成全排列
    dfs(nums, numsSize, result, returnSize, temp, used, 0);

    // 设置每个排列的列大小
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    // 释放临时数组
    free(temp);
    free(used);

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
    int nums[] = { 1, 1, 2 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;
    int** permutations = permuteUnique(nums, numsSize, &returnSize, &returnColumnSizes);

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

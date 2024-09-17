/*
题目:

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

Given an array of strings, group anagrams together.

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

说明：

    所有输入均为小写字母。
    不考虑答案输出的顺序。

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // 辅助函数，用于排序字符串中的字符
int cmpFunc(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

// 主函数：分组字母异位词
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // 初始化变量
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(strsSize * sizeof(int)); // 每组的大小
    char*** result = (char***)malloc(strsSize * sizeof(char**)); // 最终返回的结果

    // 用于保存已经分组的字符串
    char** sortedStrs = (char**)malloc(strsSize * sizeof(char*));
    for (int i = 0; i < strsSize; i++) {
        sortedStrs[i] = strdup(strs[i]); // 复制字符串
        qsort(sortedStrs[i], strlen(sortedStrs[i]), sizeof(char), cmpFunc); // 排序字符串
    }

    // 用于标记哪些字符串已经被分组
    int* grouped = (int*)calloc(strsSize, sizeof(int));

    for (int i = 0; i < strsSize; i++) {
        if (grouped[i]) continue; // 如果已经分组，跳过
        grouped[i] = 1;
        result[*returnSize] = (char**)malloc(strsSize * sizeof(char*)); // 创建新组
        result[*returnSize][0] = strs[i];
        (*returnColumnSizes)[*returnSize] = 1; // 初始化组的大小为1

        // 查找其他与当前字符串属于同一组的字符串
        for (int j = i + 1; j < strsSize; j++) {
            if (!grouped[j] && strcmp(sortedStrs[i], sortedStrs[j]) == 0) {
                grouped[j] = 1;
                result[*returnSize][(*returnColumnSizes)[*returnSize]] = strs[j];
                (*returnColumnSizes)[*returnSize] += 1; // 该组的大小加1
            }
        }

        (*returnSize)++; // 组数加1
    }

    // 释放排序后的字符串副本
    for (int i = 0; i < strsSize; i++) {
        free(sortedStrs[i]);
    }
    free(sortedStrs);
    free(grouped);

    return result;
}

// 测试函数
int main() {
    // 原始字符串数组
    const char* originalStrs[] = { "eat", "tea", "tan", "ate", "nat", "bat" };
    int strsSize = 6;
    char** strs = (char**)malloc(strsSize * sizeof(char*));

    // 复制每个字符串到新的可修改数组
    for (int i = 0; i < strsSize; i++) {
        strs[i] = strdup(originalStrs[i]);
    }

    int returnSize;
    int* returnColumnSizes;

    char*** result = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    // 打印结果
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("\"%s\"", result[i][j]);
            if (j < returnColumnSizes[i] - 1) printf(", ");
        }
        printf("]\n");
        free(result[i]); // 释放内存
    }

    free(result); // 释放结果数组
    free(returnColumnSizes); // 释放列大小数组

    return 0;
}

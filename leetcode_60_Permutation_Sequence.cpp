/*
题目描述

给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：

    “123”
    “132”
    “213”
    “231”
    “312”
    “321”

给定 n 和 k，返回第 k 个排列。

说明：

    给定 n 的范围是 [1, 9]。
    给定 k 的范围是[1, n!]。

示例 1:

    输入: n = 3, k = 3
    输出: “213”

示例 2:

    输入: n = 4, k = 9
    输出: “2314”

1.阶乘数组：提前计算 n! 的每一阶乘值，以便在查找过程中使用。
2.贪心选择每一位数字：直接利用 k 来确定当前要选择的数字，然后将该数字从可用数字列表中去除。
3.保持候选数字的顺序：通过索引直接访问候选数字，不再需要移动数组元素。
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 用于计算 n! (阶乘)
int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

char* getPermutation(int n, int k) {
    // 分配结果字符串的空间
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';  // 设置字符串结束符

    // 使用布尔数组来记录数字是否已使用
    bool used[9] = { false };  // 因为 n 的最大值为 9

    k--;  // 调整 k 使其从 0 开始计数

    for (int i = 0; i < n; i++) {
        int fact = factorial(n - 1 - i);  // 计算 (n-1)! 的值
        int index = k / fact;             // 当前要选择的数字索引
        k %= fact;                        // 更新 k

        // 查找未使用的第 index 个数字
        int num = 1;
        for (int j = 0; j <= index; num++) {
            if (!used[num - 1]) {
                j++;  // 只计算未使用的数字
            }
        }
        num--;  // 调整回有效数字
        result[i] = num + '0';  // 将数字加入结果
        used[num - 1] = true;   // 标记该数字已使用
    }

    return result;
}
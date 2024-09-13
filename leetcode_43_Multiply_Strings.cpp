/*
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

 

示例 1:

输入: num1 = "2", num2 = "3"
输出: "6"

示例 2:

输入: num1 = "123", num2 = "456"
输出: "56088"

 

提示：

    1 <= num1.length, num2.length <= 200
    num1 和 num2 只能由数字组成。
    num1 和 num2 都不包含任何前导零，除了数字0本身。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2) {
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        // 乘数中有0，直接返回"0"
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }

    int num1_length = strlen(num1);
    int num2_length = strlen(num2);
    int result_length = num1_length + num2_length;

    // 动态分配数组，用于存储中间乘积结果
    int* temp_arr = (int*)calloc(result_length, sizeof(int));

    // 执行竖式乘法
    for (int i = num1_length - 1; i >= 0; i--) {
        for (int j = num2_length - 1; j >= 0; j--) {
            int mult = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;       // 乘积的高位
            int p2 = i + j + 1;   // 乘积的低位

            int sum = mult + temp_arr[p2];

            temp_arr[p2] = sum % 10;      // 低位存储个位数
            temp_arr[p1] += sum / 10;     // 高位存储进位
        }
    }

    // 找到第一个非零的位置
    int start = 0;
    while (start < result_length && temp_arr[start] == 0) {
        start++;
    }

    // 动态分配返回字符串的空间
    char* result = (char*)malloc((result_length - start + 1) * sizeof(char));
    int index = 0;

    // 将结果数组转换为字符串
    for (int i = start; i < result_length; i++) {
        result[index++] = temp_arr[i] + '0';
    }

    result[index] = '\0';  // 结束符

    // 释放临时数组
    free(temp_arr);

    return result;
}



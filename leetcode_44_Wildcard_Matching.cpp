/*
给定一个字符串 (s) 和一个字符模式 § ，实现一个支持 ‘?’ 和 ‘*’ 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool isMatch(char* s, char* p) {
    int sLen = 0, pLen = 0;
    while (s[sLen] != '\0') sLen++;
    while (p[pLen] != '\0') pLen++;

    int sIndex = 0, pIndex = 0;
    int starIndex = -1, sTempIndex = -1;

    while (sIndex < sLen) {
        // 匹配字符或 '?'
        if (p[pIndex] == '?' || p[pIndex] == s[sIndex]) {
            sIndex++;
            pIndex++;
        }
        // 遇到 '*'
        else if (p[pIndex] == '*') {
            // 记录 '*' 的位置和当前匹配的字符串索引
            starIndex = pIndex;
            sTempIndex = sIndex;
            pIndex++; // 继续匹配模式中的下一个字符
        }
        // 回溯到上一个 '*'，尝试匹配更多字符
        else if (starIndex != -1) {
            pIndex = starIndex + 1;
            sTempIndex++;
            sIndex = sTempIndex;
        }
        // 无法匹配的情况
        else {
            return false;
        }
    }

    // 检查模式剩下的部分是否全是 '*'
    while (p[pIndex] == '*') {
        pIndex++;
    }

    // 如果模式已遍历完，则匹配成功
    return p[pIndex] == '\0';
}
/*
我们使用一个二维数组 dp[i][j] 来表示字符串 s[0...i-1] 和模式 p[0...j-1] 是否匹配。

状态转移方程：
如果 p[j-1] == s[i-1] 或者 p[j-1] == '?'，那么 dp[i][j] = dp[i-1][j-1]。也就是说，如果模式的当前字符匹配字符串的当前字符，则看前面的部分是否匹配。

如果 p[j-1] == '*'，那么 * 可以匹配空字符串或任意字符组合，有两种情况：

dp[i][j] = dp[i][j-1]：即 * 匹配空字符的情况。
dp[i][j] = dp[i-1][j]：即 * 匹配字符串的当前字符，这样模式的 * 仍然可以匹配剩下的字符串。
初始条件：dp[0][0] = true，因为空字符串和空模式是匹配的。
*/
bool isMatch1(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);

    bool* dp = (bool*)malloc((n + 1) * sizeof(bool));

    //空字符串和空模式匹配
    dp[0] = true;

    // 初始化dp数组第一行，处理空字符串的情况
    for (int j = 1; j <= n; j++){
        if (p[j - 1] == '*') {
            dp[j] = dp[j - 1];
        }
    }
    // 开始处理每个字符
    for (int i = 1; i <= m; i++) {
        bool prev = dp[0];  // 记录 dp[i-1][j-1] 的值
        dp[0] = false;  // 当前行开头置为 false，因为空字符串和非空 s 不匹配
        for (int j = 1; j <= n; j++) {
            bool temp = dp[j];  // 暂存当前 dp[j] 的值，以备后续更新
            if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                dp[j] = prev;
            }
            else if (p[j - 1] == '*') {
                dp[j] = dp[j - 1] || dp[j];
            }
            else {
                dp[j] = false;
            }
            prev = temp;  // 更新 prev 为下一次循环的 dp[i-1][j-1]
        }
    }

    // 最终结果在 dp[n] 中
    bool result = dp[n];

    // 释放动态分配的内存
    free(dp);

    return result;
}
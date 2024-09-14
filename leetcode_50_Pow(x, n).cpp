/*
题目描述

实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。

示例 1：

输入：x = 2.00000, n = 10
输出：1024.00000

示例 2：

输入：x = 2.10000, n = 3
输出：9.26100

示例 3：

输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25



提示：
    -100.0 < x < 100.0
    -231 <= n <= 231-1
    n 是一个整数
    要么 x 不为零，要么 n > 0 。
    -104 <= xn <= 104

方法一：数学（快速幂）

快速幂算法的核心思想是将幂指数 nn 拆分为若干个二进制位上的 11 的和，然后将 xx 的 nn 次幂转化为 xx 的若干个幂的乘积。

时间复杂度 O(log⁡n)O(logn)，空间复杂度 O(1)O(1)。其中 nn 为幂指数。
*/
#include<stdio.h>
double qpow(double a, long long n) {
    double ans = 1;
    for (; n; n >>= 1) {
        if (n & 1) {
            ans *= a;
        }
        a *= a;
    }
    return ans;
}

double myPow(double x, int n) {
    return n >= 0 ? qpow(x, n) : 1 / qpow(x, -(long long)n);
}
int main() {
    double x = 2.0;
    int n = 10;
    printf("Result: %f\n", myPow(x, n));  // Example usage
    return 0;
}

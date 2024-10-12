/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组
是数组中的一个连续部分。



示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：

输入：nums = [1]
输出：1

示例 3：

输入：nums = [5,4,-1,7,8]
输出：23



提示：

    1 <= nums.length <= 105
    -104 <= nums[i] <= 104

*/
#include <stdio.h>
#include <stdlib.h>
int maxSubArray(int* nums, int numsSize) {
    // 初始化最大和为最小整数值
    int max = INT_MIN;

    // 用于存储当前子数组和
    int dp = nums[0];
    max = dp;  // 初始最大值等于第一个元素

    // 从第二个元素开始进行动态规划
    for (int i = 1; i < numsSize; i++) {
        // 如果 dp (即 dp[i-1]) 小于 0，直接使用 nums[i] 作为新子数组和
        if (dp < 0) {
            dp = nums[i];
        }
        else {
            dp = dp + nums[i];
        }

        // 更新最大值
        if (dp > max) {
            max = dp;
        }
    }

    return max;
}
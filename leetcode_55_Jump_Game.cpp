/*
1. 题目描述

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个位置。

示例 1:

    输入: [2,3,1,1,4]
    输出: true
    解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3步到达最后一个位置。

示例 2:

    输入: [3,2,1,0,4]
    输出: false
    解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ，所以你永远不可能到达最后一个位置。
*/
#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int maxReach = 0;  // 当前能到达的最远距离
    for (int i = 0; i < numsSize; i++) {
        // 如果当前索引 i 超过了最远可达距离，返回 false
        if (i > maxReach) {
            return false;
        }
        // 更新最远可达距离
        if (i + nums[i] > maxReach) {
            maxReach = i + nums[i];
        }
        // 如果最远可达距离已经大于等于最后一个位置，返回 true
        if (maxReach >= numsSize - 1) {
            return true;
        }
    }
    return true;
}
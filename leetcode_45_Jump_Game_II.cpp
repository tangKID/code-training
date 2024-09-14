/*
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。
示例:

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
*/
#include <stdio.h>
#include <limits.h>

int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;  // 如果数组只有一个元素，已经在终点

    int min_step = 0;  // 记录最小跳跃次数
    int max_reach = 0;  // 记录当前能跳到的最远位置
    int last_reach = 0;  // 记录上次跳跃后能到达的最远位置

    for (int i = 0; i < numsSize; i++) {
        max_reach = (i + nums[i] > max_reach) ? i + nums[i] : max_reach;

        if (i == last_reach) {  // 到达上次跳跃能到达的最远位置
            if (i != numsSize - 1) {  // 如果还没到终点，必须跳跃
                min_step++;
                last_reach = max_reach;  // 更新最远到达位置
                if (last_reach >= numsSize - 1) break;  // 如果能到终点，退出循环
            }
        }
    }

    return min_step;
}

int main() {
    int nums[] = { 2, 3, 1, 1, 4 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = jump(nums, numsSize);
    printf("最小跳跃次数是: %d\n", result);
    return 0;
}

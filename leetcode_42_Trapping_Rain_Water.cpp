/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例 1：

输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。

示例 2：

输入：height = [4,2,0,3,2,5]
输出：9

要解决这个问题，我们需要计算每个柱子在下雨后能够存储多少雨水。
主要的思路是，每一列所能存储的水量取决于它左右两边的最大高度。
对于每一列的水量，可以通过找出它左边的最高柱子和右边的最高柱子，然后计算能容纳的雨水。

设置两个指针 left 和 right，分别指向数组的左右两端。

维护两个变量 leftMax 和 rightMax，分别表示从左端到当前指针 left 的最大值，以及从右端到当前指针 right 的最大值。

每次根据较小的一侧的最大值来决定从哪边向内移动：

如果 leftMax 小于等于 rightMax，那么我们可以确定当前位置 left 能存储的水量取决于 leftMax（因为右侧肯定会有比 leftMax 更高的柱子），计算当前水量并移动 left 指针。
如果 rightMax 小于 leftMax，则移动 right 指针，并计算对应的水量。
直到 left 和 right 指针相遇时结束循环。

*/
int trap(int* height, int heightSize) {
    if (heightSize == 0) {
        return 0; // 如果没有柱子，无法储存雨水
    }

    int left = 0;
    int right = heightSize - 1;
    int leftMax = 0;
    int rightMax = 0;
    int waterTrapped = 0;

    while (left <= right) {
        if (height[left] <= height[right]) {
            // 左边的高度较小，处理左边
            if (height[left] >= leftMax) {
                leftMax = height[left]; // 更新左边的最大值
            }
            else {
                waterTrapped += leftMax - height[left]; // 计算当前柱子可以储存的水
            }
            left++; // 移动左指针
        }
        else {
            // 右边的高度较小，处理右边
            if (height[right] >= rightMax) {
                rightMax = height[right]; // 更新右边的最大值
            }
            else {
                waterTrapped += rightMax - height[right]; // 计算当前柱子可以储存的水
            }
            right--; // 移动右指针
        }
    }
    return waterTrapped; // 返回最终计算的储水量
}


/*
一、题目描述

给定一个未排序的整数数组，找出其中没有出现的最小的正整数。

示例 1:
输入: [1,2,0]
输出: 3
示例 2:
输入: [3,4,-1,1]
输出: 2
示例 3:
输入: [7,8,9,11,12]
输出: 1


*/
int firstMissingPositive(int* nums, int numsSize) {
	//第一遍遍历，确保每个元素在正确的位置上
	for (int i = 0; i < numsSize; i++)
	{
		while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
			// 交换nums[i]和nums[nums[i] -1]
			int temp = nums[nums[i] - 1];
			nums[nums[i] - 1] = nums[i];
			nums[i] = temp;
		}
	}

	// 第二遍遍历，找到第一个不符合条件的位置
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] != i + 1) {
			return i + 1;
		}
	}

	return numsSize + 1;
}
/*
һ����Ŀ����

����һ��δ������������飬�ҳ�����û�г��ֵ���С����������

ʾ�� 1:
����: [1,2,0]
���: 3
ʾ�� 2:
����: [3,4,-1,1]
���: 2
ʾ�� 3:
����: [7,8,9,11,12]
���: 1


*/
int firstMissingPositive(int* nums, int numsSize) {
	//��һ�������ȷ��ÿ��Ԫ������ȷ��λ����
	for (int i = 0; i < numsSize; i++)
	{
		while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
			// ����nums[i]��nums[nums[i] -1]
			int temp = nums[nums[i] - 1];
			nums[nums[i] - 1] = nums[i];
			nums[i] = temp;
		}
	}

	// �ڶ���������ҵ���һ��������������λ��
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] != i + 1) {
			return i + 1;
		}
	}

	return numsSize + 1;
}
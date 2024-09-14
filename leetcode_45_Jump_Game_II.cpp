/*
����һ���Ǹ��������飬�����λ������ĵ�һ��λ�á�

�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�

���Ŀ����ʹ�����ٵ���Ծ����������������һ��λ�á�
ʾ��:

����: [2,3,1,1,4]
���: 2
����: �������һ��λ�õ���С��Ծ���� 2��
     ���±�Ϊ 0 �����±�Ϊ 1 ��λ�ã��� 1 ����Ȼ���� 3 ��������������һ��λ�á�
*/
#include <stdio.h>
#include <limits.h>

int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;  // �������ֻ��һ��Ԫ�أ��Ѿ����յ�

    int min_step = 0;  // ��¼��С��Ծ����
    int max_reach = 0;  // ��¼��ǰ����������Զλ��
    int last_reach = 0;  // ��¼�ϴ���Ծ���ܵ������Զλ��

    for (int i = 0; i < numsSize; i++) {
        max_reach = (i + nums[i] > max_reach) ? i + nums[i] : max_reach;

        if (i == last_reach) {  // �����ϴ���Ծ�ܵ������Զλ��
            if (i != numsSize - 1) {  // �����û���յ㣬������Ծ
                min_step++;
                last_reach = max_reach;  // ������Զ����λ��
                if (last_reach >= numsSize - 1) break;  // ����ܵ��յ㣬�˳�ѭ��
            }
        }
    }

    return min_step;
}

int main() {
    int nums[] = { 2, 3, 1, 1, 4 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = jump(nums, numsSize);
    printf("��С��Ծ������: %d\n", result);
    return 0;
}

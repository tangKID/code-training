/*
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��

ʾ�� 1��

���룺height = [0,1,0,2,1,0,1,3,2,1,2,1]
�����6
���ͣ������������� [0,1,0,2,1,0,1,3,2,1,2,1] ��ʾ�ĸ߶�ͼ������������£����Խ� 6 ����λ����ˮ����ɫ���ֱ�ʾ��ˮ����

ʾ�� 2��

���룺height = [4,2,0,3,2,5]
�����9

Ҫ���������⣬������Ҫ����ÿ��������������ܹ��洢������ˮ��
��Ҫ��˼·�ǣ�ÿһ�����ܴ洢��ˮ��ȡ�������������ߵ����߶ȡ�
����ÿһ�е�ˮ��������ͨ���ҳ�����ߵ�������Ӻ��ұߵ�������ӣ�Ȼ����������ɵ���ˮ��

��������ָ�� left �� right���ֱ�ָ��������������ˡ�

ά���������� leftMax �� rightMax���ֱ��ʾ����˵���ǰָ�� left �����ֵ���Լ����Ҷ˵���ǰָ�� right �����ֵ��

ÿ�θ��ݽ�С��һ������ֵ���������ı������ƶ���

��� leftMax С�ڵ��� rightMax����ô���ǿ���ȷ����ǰλ�� left �ܴ洢��ˮ��ȡ���� leftMax����Ϊ�Ҳ�϶����б� leftMax ���ߵ����ӣ������㵱ǰˮ�����ƶ� left ָ�롣
��� rightMax С�� leftMax�����ƶ� right ָ�룬�������Ӧ��ˮ����
ֱ�� left �� right ָ������ʱ����ѭ����

*/
int trap(int* height, int heightSize) {
    if (heightSize == 0) {
        return 0; // ���û�����ӣ��޷�������ˮ
    }

    int left = 0;
    int right = heightSize - 1;
    int leftMax = 0;
    int rightMax = 0;
    int waterTrapped = 0;

    while (left <= right) {
        if (height[left] <= height[right]) {
            // ��ߵĸ߶Ƚ�С���������
            if (height[left] >= leftMax) {
                leftMax = height[left]; // ������ߵ����ֵ
            }
            else {
                waterTrapped += leftMax - height[left]; // ���㵱ǰ���ӿ��Դ����ˮ
            }
            left++; // �ƶ���ָ��
        }
        else {
            // �ұߵĸ߶Ƚ�С�������ұ�
            if (height[right] >= rightMax) {
                rightMax = height[right]; // �����ұߵ����ֵ
            }
            else {
                waterTrapped += rightMax - height[right]; // ���㵱ǰ���ӿ��Դ����ˮ
            }
            right--; // �ƶ���ָ��
        }
    }
    return waterTrapped; // �������ռ���Ĵ�ˮ��
}


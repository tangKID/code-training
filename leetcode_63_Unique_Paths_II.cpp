/*
1. ��Ŀ����

һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����

������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������

���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����

�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��

˵����m �� n ��ֵ�������� 100��

ʾ�� 1:

����: [ [0,0,0], [0,1,0], [0,0,0] ]
���: 2
����: 3x3 ��������м���һ���ϰ��
�����Ͻǵ����½�һ���� 2 ����ͬ��·����

    ���� -> ���� -> ���� -> ����
    ���� -> ���� -> ���� -> ����
*/
#include <stdio.h>
#include <stdlib.h>

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    int m = obstacleGridSize;
    int n = *obstacleGridColSize;

    // ��̬����dp���飬��СΪ����n
    int* dp = (int*)malloc(sizeof(int) * n);

    // ��ʼ��dp���飬�����һ���Ƿ����ϰ���
    dp[0] = (obstacleGrid[0][0] == 1) ? 0 : 1;

    // ��ʼ����һ�е�dpֵ���ϰ���֮���·����Ϊ0
    for (int j = 1; j < n; j++) {
        dp[j] = (obstacleGrid[0][j] == 1 || dp[j - 1] == 0) ? 0 : 1;
    }

    // ���dp����
    for (int i = 1; i < m; i++) {
        // �����һ�У���һ��ֻ��������������
        dp[0] = (obstacleGrid[i][0] == 1) ? 0 : dp[0];

        for (int j = 1; j < n; j++) {
            // ������ϰ��dp[j]Ϊ0���������dp[j]
            if (obstacleGrid[i][j] == 1) {
                dp[j] = 0;
            }
            else {
                dp[j] += dp[j - 1];  // dp[j] = �Ϸ���ֵ + �󷽵�ֵ
            }
        }
    }

    int result = dp[n - 1];  // ���½ǵ�ֵ���ǽ��
    free(dp);  // �ͷŶ�̬������ڴ�
    return result;
}
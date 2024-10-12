/*
����һ�� m �� n �еľ��� matrix ���밴�� ˳ʱ������˳�� �����ؾ����е�����Ԫ�ء�



ʾ�� 1��

���룺matrix = [[1,2,3],[4,5,6],[7,8,9]]
�����[1,2,3,6,9,8,7,4,5]

ʾ�� 2��

���룺matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
�����[1,2,3,4,8,12,11,10,9,5,6,7]



��ʾ��

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

    ����˳��Ϊ������ -> ���� -> ���� -> ���� -> ���ϣ�Ȼ���ڲ��ظ���������˳��
*/
#include <stdlib.h>
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    *returnSize = 0;
    if (matrixSize == 0 || matrixColSize[0] == 0) return NULL;
    int top = 0;  //��0��ʼ��ָ�� matrix �ĵ�һ�С�
    int bottom = matrixSize - 1; //�� m-1 ��ʼ��ָ�� matrix �����һ�С�
    int left = 0;  //��0��ʼ��ָ�� matrix �ĵ�һ�С�
    int right = matrixColSize[0]-1; //�� n-1 ��ʼ��ָ��matix �����һ�С�
    int totalElements = matrixSize * matrixColSize[0];  // �����е���Ԫ����
    int* result = (int*)malloc(totalElements * sizeof(int));
    
    while(top <= bottom && left <= right) {
        
        for (int i = left; i <= right; i++)
        {
            // �������ұ���top��
            result[(*returnSize)++] = matrix[top][i];
        }
        top++; //������top�к�top++

        for (int i = top; i <= bottom; i++) {
            // ���ϵ��±���right��
            result[(*returnSize)++] = matrix[i][right];
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                //���ҵ������bottom��
                result[(*returnSize)++] = matrix[bottom][i];
            }
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--){
                //���µ��ϱ���left��
                result[(*returnSize)++] = matrix[i][left];
            }
            left++;
        }
    }
    return result;
}
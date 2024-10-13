/*
1. ��Ŀ����

����һ������ļ��ϣ���ϲ������ص������䡣

ʾ�� 1:

    ����: [[1,3],[2,6],[8,10],[15,18]]
    ���: [[1,6],[8,10],[15,18]]
    ����: ����[1,3] �� [2,6] �ص�, �����Ǻϲ�Ϊ [1,6].

ʾ�� 2:

    ����: [[1,4],[4,5]]
    ���: [[1,5]]
    ����: ���� [1,4] �� [4,5] �ɱ���Ϊ�ص����䡣
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int compare(const void* a, const void* b) {
    // ���� qsort �ıȽϺ��������������ʼλ����������
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    return intervalA[0] - intervalB[0];
}


int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    //�ȶ�intervals����ʼλ������
    qsort(intervals, intervalsSize, sizeof(int*), compare);

    int** result = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int*));

    //���ڴ洢�ϲ�����������
    int mergedCount = 0;
    // ��ʼ����һ������
    result[mergedCount] = (int*)malloc(2 * sizeof(int));
    result[mergedCount][0] = intervals[0][0];
    result[mergedCount][1] = intervals[0][1];
    (*returnColumnSizes)[mergedCount] = 2;
    mergedCount++;

    // ��������������кϲ�
    for (int i = 1; i < intervalsSize; i++) {
        int* currentInterval = intervals[i];
        int* lastMergedInterval = result[mergedCount - 1];

        // �����ǰ��������һ���ϲ������ص������½���λ��
        if (currentInterval[0] <= lastMergedInterval[1]) {
            lastMergedInterval[1] = (lastMergedInterval[1] > currentInterval[1]) ? lastMergedInterval[1] : currentInterval[1];
        }
        else {
            // ���û���ص���ֱ����ӵ�ǰ����
            result[mergedCount] = (int*)malloc(2 * sizeof(int));
            result[mergedCount][0] = currentInterval[0];
            result[mergedCount][1] = currentInterval[1];
            (*returnColumnSizes)[mergedCount] = 2;
            mergedCount++;
        }
    }
    // ���÷���ֵ
    *returnSize = mergedCount;
    return result;
}
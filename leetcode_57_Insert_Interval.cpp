/*
�ڸ����ķ��ص������б��в���һ���µ����䣬���ڲ���󱣳���Щ������ص�������µ����������������ص���������Ҫ���ص�������ϲ���

����˼·��
���裺
��ʼ����

����һ�������� result �����洢�ϲ�������䡣
ά��һ���µ����� mergedInterval���ں��ʵ�λ�úϲ��µ����䡣
����ԭʼ�������飺

����ÿһ�����䣬�����
��ǰ������ newInterval ֮ǰ��ֱ�ӽ������ result��
��ǰ������ newInterval ֮����� newInterval ��δ���룬�� newInterval �ϲ��� result �У��ټ��뵱ǰ���䡣
��ǰ������ newInterval �ص������� newInterval �ķ�Χ������ newInterval �뵱ǰ����ϲ���
��� newInterval �Ƿ��Ѳ��룺

������ɺ���� newInterval ��δ�����룬��Ҫ�ֶ����롣
�ڴ���䣺

��Ϊ����Ҫ�󷵻ص�������д�С���鶼��Ҫ��̬���䣬�����Ҫʹ�� malloc �����ڴ棬���ڷ���ʱ��ȷ���á�
*/

#include <stdlib.h>

// Helper function to get the maximum of two integers
int max(int a, int b) {
    return a > b ? a : b;
}

// Helper function to get the minimum of two integers
int min(int a, int b) {
    return a < b ? a : b;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    // Allocate memory for result array and the column sizes array
    int** result = (int**)malloc((intervalsSize + 1) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((intervalsSize + 1) * sizeof(int));

    int idx = 0; // Result array index
    int i = 0;   // Original intervals array index

    // Add all intervals that end before the new interval starts
    while (i < intervalsSize && intervals[i][1] < newInterval[0]) {
        result[idx] = (int*)malloc(2 * sizeof(int));
        result[idx][0] = intervals[i][0];
        result[idx][1] = intervals[i][1];
        (*returnColumnSizes)[idx] = 2;
        idx++;
        i++;
    }

    // Merge all overlapping intervals with the new interval
    while (i < intervalsSize && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }

    // Add the merged new interval
    result[idx] = (int*)malloc(2 * sizeof(int));
    result[idx][0] = newInterval[0];
    result[idx][1] = newInterval[1];
    (*returnColumnSizes)[idx] = 2;
    idx++;

    // Add the rest of the intervals that start after the new interval
    while (i < intervalsSize) {
        result[idx] = (int*)malloc(2 * sizeof(int));
        result[idx][0] = intervals[i][0];
        result[idx][1] = intervals[i][1];
        (*returnColumnSizes)[idx] = 2;
        idx++;
        i++;
    }

    // Set the return size
    *returnSize = idx;

    return result;
}

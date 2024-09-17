/*
1. ��Ŀ����

����һ��û���ظ����ֵ����У����������п��ܵ�ȫ���С�

ʾ��:

    ����: [1,2,3]
    ���:
    [
    [1,2,3],
    [1,3,2],
    [2,1,3],
    [2,3,1],
    [3,1,2],
    [3,2,1]
    ]
*/
#include <stdio.h>
#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void dfs(int* nums, int numsSize, int** result, int* returnSize, int start) {
    if (start == numsSize) {

        result[*returnSize] = (int*)malloc(numsSize * sizeof(int));

        for (int i = 0; i < numsSize; i++)
        {
            result[*returnSize][i] = nums[i];
        }
        (*returnSize)++;
        return;
    }
    for (int i = 0; i < numsSize; i++)
    {
        swap(nums, start, i);  // ������ǰԪ����startλ�� 
        dfs(nums, numsSize, result, returnSize, start + 1); // �ݹ鴦�����Ԫ��
        swap(nums, start, i); // ���ݣ��ָ�ԭ����

    }

}


void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}


int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    //����ȫ���е�����ΪnumsSize!
    int totalPermutations = 1;
    for (int i = 2; i <= numsSize; i++)
    {
        totalPermutations *= i;
    }
    // ����洢����Ŀռ�
    int** result = (int**)malloc(totalPermutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));

    // ���������������ȫ����
    dfs(nums, numsSize, result, returnSize, 0);

    // ����ÿ�����е��д�С
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    return result;

}

// ��ӡ��ά����
void printPermutations(int** permutations, int returnSize, int numsSize) {
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            printf("%d ", permutations[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nums[] = { 1, 2, 3 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;
    int** permutations = permute(nums, numsSize, &returnSize, &returnColumnSizes);

    // ��ӡ���ɵ�ȫ����
    printPermutations(permutations, returnSize, numsSize);

    // �ͷ��ڴ�
    for (int i = 0; i < returnSize; i++) {
        free(permutations[i]);
    }
    free(permutations);
    free(returnColumnSizes);

    return 0;
}

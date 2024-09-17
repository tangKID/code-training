#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���������е�����Ԫ��
void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

// �ȽϺ���������qsort��������
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// ������������ݹ麯��������ȫ���У������ظ�
void dfs(int* nums, int numsSize, int** result, int* returnSize, int* temp, int* used, int depth) {
    if (depth == numsSize) {
        // ������ݹ���ȵ������鳤��ʱ������һ���µ�����
        result[*returnSize] = (int*)malloc(numsSize * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            result[*returnSize][i] = temp[i];
        }
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        // �����Ԫ���Ѿ���ʹ�ã�����
        if (used[i]) continue;
        // ��֦�������ظ�����
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

        // ���Ԫ�ر�ʹ��
        used[i] = 1;
        temp[depth] = nums[i];
        dfs(nums, numsSize, result, returnSize, temp, used, depth + 1);
        // ���ݣ��ָ�״̬
        used[i] = 0;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    // ����ȫ���е�����Ϊ numsSize!
    int totalPermutations = 1;
    for (int i = 2; i <= numsSize; i++) {
        totalPermutations *= i;
    }

    // ����洢����Ŀռ�
    int** result = (int**)malloc(totalPermutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));

    // ���������Է���ʶ���ظ�Ԫ��
    qsort(nums, numsSize, sizeof(int), compare);

    // ��ʼ�����ڴ洢��ǰ���е���ʱ����
    int* temp = (int*)malloc(numsSize * sizeof(int));
    // ��ʼ�������ж�Ԫ���Ƿ�ʹ�õ�����
    int* used = (int*)calloc(numsSize, sizeof(int));

    // ���������������ȫ����
    dfs(nums, numsSize, result, returnSize, temp, used, 0);

    // ����ÿ�����е��д�С
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    // �ͷ���ʱ����
    free(temp);
    free(used);

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
    int nums[] = { 1, 1, 2 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;
    int** permutations = permuteUnique(nums, numsSize, &returnSize, &returnColumnSizes);

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

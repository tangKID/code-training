/*
��Ŀ:

����һ���ַ������飬����ĸ��λ�������һ����ĸ��λ��ָ��ĸ��ͬ�������в�ͬ���ַ�����

Given an array of strings, group anagrams together.

ʾ��:

����: ["eat", "tea", "tan", "ate", "nat", "bat"],
���:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

˵����

    ���������ΪСд��ĸ��
    �����Ǵ������˳��

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // �������������������ַ����е��ַ�
int cmpFunc(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

// ��������������ĸ��λ��
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // ��ʼ������
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(strsSize * sizeof(int)); // ÿ��Ĵ�С
    char*** result = (char***)malloc(strsSize * sizeof(char**)); // ���շ��صĽ��

    // ���ڱ����Ѿ�������ַ���
    char** sortedStrs = (char**)malloc(strsSize * sizeof(char*));
    for (int i = 0; i < strsSize; i++) {
        sortedStrs[i] = strdup(strs[i]); // �����ַ���
        qsort(sortedStrs[i], strlen(sortedStrs[i]), sizeof(char), cmpFunc); // �����ַ���
    }

    // ���ڱ����Щ�ַ����Ѿ�������
    int* grouped = (int*)calloc(strsSize, sizeof(int));

    for (int i = 0; i < strsSize; i++) {
        if (grouped[i]) continue; // ����Ѿ����飬����
        grouped[i] = 1;
        result[*returnSize] = (char**)malloc(strsSize * sizeof(char*)); // ��������
        result[*returnSize][0] = strs[i];
        (*returnColumnSizes)[*returnSize] = 1; // ��ʼ����Ĵ�СΪ1

        // ���������뵱ǰ�ַ�������ͬһ����ַ���
        for (int j = i + 1; j < strsSize; j++) {
            if (!grouped[j] && strcmp(sortedStrs[i], sortedStrs[j]) == 0) {
                grouped[j] = 1;
                result[*returnSize][(*returnColumnSizes)[*returnSize]] = strs[j];
                (*returnColumnSizes)[*returnSize] += 1; // ����Ĵ�С��1
            }
        }

        (*returnSize)++; // ������1
    }

    // �ͷ��������ַ�������
    for (int i = 0; i < strsSize; i++) {
        free(sortedStrs[i]);
    }
    free(sortedStrs);
    free(grouped);

    return result;
}

// ���Ժ���
int main() {
    // ԭʼ�ַ�������
    const char* originalStrs[] = { "eat", "tea", "tan", "ate", "nat", "bat" };
    int strsSize = 6;
    char** strs = (char**)malloc(strsSize * sizeof(char*));

    // ����ÿ���ַ������µĿ��޸�����
    for (int i = 0; i < strsSize; i++) {
        strs[i] = strdup(originalStrs[i]);
    }

    int returnSize;
    int* returnColumnSizes;

    char*** result = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    // ��ӡ���
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("\"%s\"", result[i][j]);
            if (j < returnColumnSizes[i] - 1) printf(", ");
        }
        printf("]\n");
        free(result[i]); // �ͷ��ڴ�
    }

    free(result); // �ͷŽ������
    free(returnColumnSizes); // �ͷ��д�С����

    return 0;
}

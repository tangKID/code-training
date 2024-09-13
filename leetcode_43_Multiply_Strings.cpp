/*
�����������ַ�����ʽ��ʾ�ķǸ����� num1 �� num2������ num1 �� num2 �ĳ˻������ǵĳ˻�Ҳ��ʾΪ�ַ�����ʽ��

ע�⣺����ʹ���κ����õ� BigInteger ���ֱ�ӽ�����ת��Ϊ������

 

ʾ�� 1:

����: num1 = "2", num2 = "3"
���: "6"

ʾ�� 2:

����: num1 = "123", num2 = "456"
���: "56088"

 

��ʾ��

    1 <= num1.length, num2.length <= 200
    num1 �� num2 ֻ����������ɡ�
    num1 �� num2 ���������κ�ǰ���㣬��������0����
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2) {
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        // ��������0��ֱ�ӷ���"0"
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }

    int num1_length = strlen(num1);
    int num2_length = strlen(num2);
    int result_length = num1_length + num2_length;

    // ��̬�������飬���ڴ洢�м�˻����
    int* temp_arr = (int*)calloc(result_length, sizeof(int));

    // ִ����ʽ�˷�
    for (int i = num1_length - 1; i >= 0; i--) {
        for (int j = num2_length - 1; j >= 0; j--) {
            int mult = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;       // �˻��ĸ�λ
            int p2 = i + j + 1;   // �˻��ĵ�λ

            int sum = mult + temp_arr[p2];

            temp_arr[p2] = sum % 10;      // ��λ�洢��λ��
            temp_arr[p1] += sum / 10;     // ��λ�洢��λ
        }
    }

    // �ҵ���һ�������λ��
    int start = 0;
    while (start < result_length && temp_arr[start] == 0) {
        start++;
    }

    // ��̬���䷵���ַ����Ŀռ�
    char* result = (char*)malloc((result_length - start + 1) * sizeof(char));
    int index = 0;

    // ���������ת��Ϊ�ַ���
    for (int i = start; i < result_length; i++) {
        result[index++] = temp_arr[i] + '0';
    }

    result[index] = '\0';  // ������

    // �ͷ���ʱ����
    free(temp_arr);

    return result;
}



/*
����һ���ַ��� (s) ��һ���ַ�ģʽ �� ��ʵ��һ��֧�� ��?�� �� ��*�� ��ͨ���ƥ�䡣

'?' ����ƥ���κε����ַ���
'*' ����ƥ�������ַ������������ַ�������
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool isMatch(char* s, char* p) {
    int sLen = 0, pLen = 0;
    while (s[sLen] != '\0') sLen++;
    while (p[pLen] != '\0') pLen++;

    int sIndex = 0, pIndex = 0;
    int starIndex = -1, sTempIndex = -1;

    while (sIndex < sLen) {
        // ƥ���ַ��� '?'
        if (p[pIndex] == '?' || p[pIndex] == s[sIndex]) {
            sIndex++;
            pIndex++;
        }
        // ���� '*'
        else if (p[pIndex] == '*') {
            // ��¼ '*' ��λ�ú͵�ǰƥ����ַ�������
            starIndex = pIndex;
            sTempIndex = sIndex;
            pIndex++; // ����ƥ��ģʽ�е���һ���ַ�
        }
        // ���ݵ���һ�� '*'������ƥ������ַ�
        else if (starIndex != -1) {
            pIndex = starIndex + 1;
            sTempIndex++;
            sIndex = sTempIndex;
        }
        // �޷�ƥ������
        else {
            return false;
        }
    }

    // ���ģʽʣ�µĲ����Ƿ�ȫ�� '*'
    while (p[pIndex] == '*') {
        pIndex++;
    }

    // ���ģʽ�ѱ����꣬��ƥ��ɹ�
    return p[pIndex] == '\0';
}
/*
����ʹ��һ����ά���� dp[i][j] ����ʾ�ַ��� s[0...i-1] ��ģʽ p[0...j-1] �Ƿ�ƥ�䡣

״̬ת�Ʒ��̣�
��� p[j-1] == s[i-1] ���� p[j-1] == '?'����ô dp[i][j] = dp[i-1][j-1]��Ҳ����˵�����ģʽ�ĵ�ǰ�ַ�ƥ���ַ����ĵ�ǰ�ַ�����ǰ��Ĳ����Ƿ�ƥ�䡣

��� p[j-1] == '*'����ô * ����ƥ����ַ����������ַ���ϣ������������

dp[i][j] = dp[i][j-1]���� * ƥ����ַ��������
dp[i][j] = dp[i-1][j]���� * ƥ���ַ����ĵ�ǰ�ַ�������ģʽ�� * ��Ȼ����ƥ��ʣ�µ��ַ�����
��ʼ������dp[0][0] = true����Ϊ���ַ����Ϳ�ģʽ��ƥ��ġ�
*/
bool isMatch1(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);

    bool* dp = (bool*)malloc((n + 1) * sizeof(bool));

    //���ַ����Ϳ�ģʽƥ��
    dp[0] = true;

    // ��ʼ��dp�����һ�У�������ַ��������
    for (int j = 1; j <= n; j++){
        if (p[j - 1] == '*') {
            dp[j] = dp[j - 1];
        }
    }
    // ��ʼ����ÿ���ַ�
    for (int i = 1; i <= m; i++) {
        bool prev = dp[0];  // ��¼ dp[i-1][j-1] ��ֵ
        dp[0] = false;  // ��ǰ�п�ͷ��Ϊ false����Ϊ���ַ����ͷǿ� s ��ƥ��
        for (int j = 1; j <= n; j++) {
            bool temp = dp[j];  // �ݴ浱ǰ dp[j] ��ֵ���Ա���������
            if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                dp[j] = prev;
            }
            else if (p[j - 1] == '*') {
                dp[j] = dp[j - 1] || dp[j];
            }
            else {
                dp[j] = false;
            }
            prev = temp;  // ���� prev Ϊ��һ��ѭ���� dp[i-1][j-1]
        }
    }

    // ���ս���� dp[n] ��
    bool result = dp[n];

    // �ͷŶ�̬������ڴ�
    free(dp);

    return result;
}
/*
����

����һ���������ͷ��� head �����������������ѭ���ƶ� k �Σ������ƶ���ĵ�����ͷ��㡣

��������

    �����еĽ������ [0, 500] ��
    -100 <= Node.val <= 100
    0 <= k <= 2 * 10 ^ 9



Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]


Input: head = [0,1,2], k = 4
Output: [2,0,1]
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
 // ���嵥����Ľڵ�ṹ
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    // �߽��������
    if (!head || !head->next || k == 0) {
        return head;
    }

    struct ListNode* tail = head;
    int length = 1;
    while (tail->next) {
        tail = tail->next;
        length++;
    }
    // ������պϳɻ�
    tail->next = head;

    // ����ʵ����ת����
    k = k % length;
    int stepsToNewHead = length - k;

    // �ҵ��µ�β�ڵ㲢�Ͽ�����
    struct ListNode* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }
    struct ListNode* newHead = newTail->next;
    newTail->next = NULL;  // �Ͽ���

    return newHead;
}
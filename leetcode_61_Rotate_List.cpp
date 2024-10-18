/*
题意

给定一个单链表的头结点 head ，将这个单链表向右循环移动 k 次，返回移动后的单链表头结点。

数据限制

    链表中的结点数在 [0, 500] 内
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
 // 定义单链表的节点结构
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    // 边界情况处理
    if (!head || !head->next || k == 0) {
        return head;
    }

    struct ListNode* tail = head;
    int length = 1;
    while (tail->next) {
        tail = tail->next;
        length++;
    }
    // 将链表闭合成环
    tail->next = head;

    // 计算实际旋转次数
    k = k % length;
    int stepsToNewHead = length - k;

    // 找到新的尾节点并断开链表
    struct ListNode* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }
    struct ListNode* newHead = newTail->next;
    newTail->next = NULL;  // 断开环

    return newHead;
}
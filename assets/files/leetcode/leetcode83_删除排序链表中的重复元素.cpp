#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        ListNode* current = head;
        while (current) {
            while (current->next && current->next->val == current->val) {
                ListNode *temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            current = current->next;
        }
        return head;
    }
};

// 释放链表内存的函数
void deleteList(ListNode *head)
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solution;
    ListNode* head = nullptr;
    int n;
    cin >> n;
    ListNode* current = nullptr;
    for (int i = 0; i < n; i++) {
        int input;
        cin >> input;
        if (!head) {
            head = new ListNode(input);
            current = head;
        } else {
            ListNode* newNode = new ListNode(input);
            current -> next = newNode;
            current = newNode;
        }
    }

    ListNode* expectedHead = solution.deleteDuplicates(head);
    current = expectedHead;
    while (current) {
        cout << current->val << ' ';
        current = current->next;
    }
    deleteList(expectedHead);
    return 0;
}
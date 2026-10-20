#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> visited;
        while (head != nullptr)
        {
            if (visited.count(head) > 0)
            {
                return true;
            }
            visited.insert(head);
            head = head->next;
        }
        return false;
    }
};
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {} // 为什么不是val = 0, left = nullptr, right = nullptr?
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    void inOrder(TreeNode* node, vector<int>& res) {
        if (!node) {
            res.push_back(-1);
            return;
        }
        inOrder(node->left, res);
        res.push_back(node->val);
        inOrder(node->right, res);
    }

    void preOrder(TreeNode* node, vector<int>& res) {
        if (!node) {
            res.push_back(-1);
            return;
        }
        res.push_back(node->val);
        preOrder(node->left, res);
        preOrder(node->right, res);
    }
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        vector<int> inP, inQ, preP, preQ;
        inOrder(p, inP);
        inOrder(q, inQ);
        preOrder(p, preP);
        preOrder(q, preQ);
        return inP == inQ && preP == preQ;
    }
};
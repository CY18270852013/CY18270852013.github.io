#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {} // 为什么不是val = 0, left = nullptr, right = nullptr?
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
private:
    void inOrder1(TreeNode *node, vector<int> &res)
    {
        if (!node)
        {
            res.push_back(101);
            return;
        }
        inOrder1(node->left, res);
        res.push_back(node->val);
        inOrder1(node->right, res);
    }

    void inOrder2(TreeNode *node, vector<int> &res)
    {
        if (!node)
        {
            res.push_back(101);
            return;
        }
        inOrder2(node->right, res);
        res.push_back(node->val);
        inOrder2(node->left, res);
    }

public:
    bool isSymmetric(TreeNode* root)
    {
        vector<int> res1, res2;
        inOrder1(root, res1);
        inOrder2(root, res2);
        int n = res1.size();
        for (int i = 0; i < n; i++) {
            if (res1[i] != res1[n - i - 1]) return false;
        }
        return res1 == res2;
    }
};

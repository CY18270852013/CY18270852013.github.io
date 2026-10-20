#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            return 1;
        }

        int min_depth = INT_MAX;
        if (root->left != nullptr)
        {
            min_depth = min(minDepth(root->left), min_depth);
        }
        if (root->right != nullptr)
        {
            min_depth = min(minDepth(root->right), min_depth);
        }

        return min_depth + 1;
    }
};

class Solution2 {
public:
    int minDepth(TreeNode *root) {
        static int minD = 0;
        if (root == nullptr) {
            return 0;
        }
        else if (root->left == nullptr) {
            return minDepth(root->right) + 1;
        }
        else if (root->right == nullptr) {
            return minDepth(root->left) + 1;
        }
        else {
            return min(minDepth(root->left), minDepth(root->right)) + 1;
        }
    }
};
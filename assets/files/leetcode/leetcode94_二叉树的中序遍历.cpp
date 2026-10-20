#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

// 二叉树节点定义
struct TreeNode
{
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
    // 递归法中序遍历
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        inorder(root, res);
        return res;
    }

private:
    void inorder(TreeNode *node, vector<int> &res)
    {
        if (!node)
            return;
        inorder(node->left, res);
        res.push_back(node->val);
        inorder(node->right, res);
    }
};

// 根据层序遍历输入构建二叉树
TreeNode *buildTree(const vector<string> &nodes)
{
    if (nodes.empty() || nodes[0] == "null")
        return nullptr;

    TreeNode *root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size())
    {
        TreeNode *curr = q.front();
        q.pop();

        // 左子节点
        if (i < nodes.size() && nodes[i] != "null")
        {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;

        // 右子节点
        if (i < nodes.size() && nodes[i] != "null")
        {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }

    return root;
}

// 打印二叉树（中序遍历格式）
void printTreeInorder(TreeNode *root)
{
    if (!root)
    {
        cout << "[]";
        return;
    }

    vector<int> result;
    Solution().inorderTraversal(root);

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << result[i];
        if (i != result.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

// 打印结果向量
void printVector(const vector<int> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i != vec.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

// 分割字符串
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// 清理二叉树内存
void deleteTree(TreeNode *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    Solution solution;

    cout << "=== 二叉树中序遍历（递归法）===" << endl;
    cout << "请输入二叉树的层序遍历序列（用空格分隔，'null'表示空节点）" << endl;
    cout << "示例1: 1 null 2 3" << endl;
    cout << "示例2: 5 4 8 11 null 13 4 7 2 null null null 1" << endl;
    cout << "示例3: (直接回车测试空树)" << endl;
    cout << endl;

    while (true)
    {
        cout << "请输入二叉树序列: ";
        string input;
        getline(cin, input);

        if (input.empty())
        {
            cout << "测试空树..." << endl;
            input = "";
        }

        // 处理输入
        vector<string> nodes = split(input, ' ');

        // 构建二叉树
        TreeNode *root = buildTree(nodes);

        // 执行中序遍历
        vector<int> result = solution.inorderTraversal(root);

        // 输出结果
        cout << "输入二叉树: ";
        printTreeInorder(root);
        cout << endl;

        cout << "中序遍历结果: ";
        printVector(result);
        cout << endl
             << endl;

        // 清理内存
        deleteTree(root);

        // 询问是否继续
        cout << "是否继续测试？(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // 清除输入缓冲区

        if (choice != 'y' && choice != 'Y')
        {
            break;
        }
        cout << endl;
    }

    cout << "程序结束，谢谢使用！" << endl;
    return 0;
}
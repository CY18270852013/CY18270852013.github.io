#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

// 广度优先搜索
class Solution1
{
public:
    int numWays(int n, vector<vector<int>> &relation, int k)
    {
        vector<vector<int>> graph(n);
        for (auto &rel : relation)
        {
            graph[rel[0]].push_back(rel[1]);
        }
        queue<int> q;
        q.push(0);

        int step = 0;
        int count = 0;
        while (!q.empty() && step < k)
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                int curr = q.front();
                q.pop();

                for (auto &next : graph[curr])
                {
                    q.push(next);
                }
            }
            step++;
        }
        if (step == k)
        {
            while (!q.empty())
            {
                if (q.front() == n - 1)
                {
                    count++;
                }
                q.pop();
            }
        }
        return count;
    }
};

// 深度优先搜索
class Solution2
{
public:
    int numWays(int n, vector<vector<int>> &relation, int k)
    {
        vector<vector<int>> edges(n);
        for (auto &edge : relation)
        {
            int src = edge[0], dst = edge[1];
            edges[src].push_back(dst);
        }

        int ways = 0;
        function<void(int, int)> dfs = [&](int index, int steps)
        {
            if (steps == k)
            {
                if (index == n - 1)
                {
                    ++ways;
                }
                return;
            }
            for (int to : edges[index])
            {
                dfs(to, steps + 1);
            }
        };
        dfs(0, 0);
        return ways;
    }
};

// 动态规划
class Solution3
{
public:
    int numWays(int n, vector<vector<int>> &relation, int k)
    {
        vector<vector<int>> dp(k + 1, vector<int>(n));
        dp[0][0] = 1;
        for (int i = 0; i < k; i++)
        {
            for (auto &edge : relation)
            {
                int src = edge[0], dst = edge[1];
                dp[i + 1][dst] += dp[i][src];
            }
        }
        return dp[k][n - 1];
    }
};

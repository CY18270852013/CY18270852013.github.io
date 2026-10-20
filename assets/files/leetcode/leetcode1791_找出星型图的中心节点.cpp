#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int findCenter(vector<vector<int>> &edges)
    {
        int n = edges.size();
        vector<int> degree(n + 2, 0);
        for (int i = 0; i < n; i++)
        {
            degree[edges[i][0]]++;
            degree[edges[i][1]]++;
        }
        for (int j = 1; j <= n + 1; j++)
        {
            if (degree[j] == n)
            {
                return j;
            }
        }
        return 0;
    }
};
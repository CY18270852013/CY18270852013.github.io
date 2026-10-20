#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    int findJudge(int n, vector<vector<int>> &trust)
    {
        unordered_map<int, int> trustCount;
        unordered_map<int, int> beTrusted;
        int number = trust.size();
        for (int i = 0; i < number; i++)
        {
            trustCount[trust[i][0]]++;
            beTrusted[trust[i][1]]++;
        }
        for (int j = 1; j <= n; j++)
        {
            if (trustCount.find(j) == trustCount.end() && beTrusted[j] == n - 1)
            {
                return j;
            }
        }
        return -1;
    }
};
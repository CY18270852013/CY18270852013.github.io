#include <iostream>
#include <vector>

using namespace std;

class Solution1
{
public:
    vector<int> countBits(int n)
    {
        vector<int> ans(n + 1, 0);
        for (int i = 0; i <= n; i++)
        {
            ans[i] = __builtin_popcount(i);
        }
        return ans;
    }
};

class Solution2
{
public:
    vector<int> countBits(int n)
    {
        vector<int> ans(n + 1, 0);
        int highBit = 0;
        for (int i = 1; i <= n; i++)
        {
            if ((i & (i - 1)) == 0)
            {
                highBit = i;
            }
            ans[i] = ans[i - highBit] + 1;
        }
        return ans;
    }
};
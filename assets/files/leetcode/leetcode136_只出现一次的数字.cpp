#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        unordered_map<int, int> up;
        for (int n : nums)
        {
            up[n]++;
        }
        for (auto &[n, count] : up)
        {
            if (count == 1)
            {
                return n;
            }
        }
        return 0;
    }
};
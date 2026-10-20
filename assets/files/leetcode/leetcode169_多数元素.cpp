#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        unordered_map<int, int> counts;
        int major = 0, number = 0;
        for (int num : nums)
        {
            counts[num]++;
            if (counts[num] > number)
            {
                major = num;
                number = counts[num];
            }
        }
        return major;
    }
};
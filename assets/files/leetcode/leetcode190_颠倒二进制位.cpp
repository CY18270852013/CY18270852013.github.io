#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution
{
public:
    int reverseBits(int n)
    {
        long long ans = 0;
        string bitStr;
        for (int i = 31; i >= 0; i--)
        {
            if (n & (1 << i))
            {
                bitStr += '1';
            }
            else
            {
                bitStr += '0';
            }
        }
        reverse(bitStr.begin(), bitStr.end());
        for (int j = 31; j > 0; j--)
        {
            ans += ((bitStr[j] - '0') * pow(2, 32 - j - 1));
        }
        if (bitStr[0] == '1')
            ans = -ans;
        return ans;
    }
};
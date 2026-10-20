#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Solution
{
public:
    int titleToNumber(string columnTitle)
    {
        int ans = 0;
        int len = columnTitle.length();
        for (int i = len - 1; i >= 0; i--)
        {
            ans = ans + ((columnTitle[len - i - 1] - 'A' + 1) * pow(26, i));
        }
        return ans;
    }
};
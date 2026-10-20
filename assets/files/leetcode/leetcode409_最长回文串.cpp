#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution1
{
public:
    int longestPalindrome(string s)
    {
        unordered_map<char, int> count;
        for (char c : s)
        {
            count[c]++;
        }
        int dou = 0, sin = 0;
        for (auto &[c, n] : count)
        {
            if (n > 1)
            {
                if (n % 2 == 0)
                {
                    dou += n;
                }
                else
                {
                    dou += n - 1;
                    sin++;
                }
            }
            else
            {
                if (n % 2 == 0)
                {
                    dou += n;
                }
                else
                {
                    sin += n;
                }
            }
        }
        int ans = dou + (sin > 0 ? 1 : 0);
        return ans;
    }
};

class Solution2
{
public:
    int longestPalindrome(string s)
    {
        unordered_map<char, int> count;
        int ans = 0;
        for (char c : s)
            ++count[c];
        for (auto p : count)
        {
            int v = p.second;
            ans += v / 2 * 2;
            if (v % 2 == 1 and ans % 2 == 0)
                ++ans;
        }
        return ans;
    }
};
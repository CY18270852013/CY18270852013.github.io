#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        int n = s.size();
        string s2;
        for (char ch : s)
        {
            if (isalnum(ch))
            {
                if (isupper(ch))
                {
                    s2 += tolower(ch);
                }
                else
                {
                    s2 += ch;
                }
            }
        }
        string s3 = s2;
        reverse(s2.begin(), s2.end());
        if (s2 == s3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
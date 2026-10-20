#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    string convertToTitle(int columnNumber)
    {
        columnNumber--;
        if (columnNumber < 26)
        {
            return string(1, 'A' + columnNumber);
        }
        return convertToTitle(columnNumber / 26) + char('A' + columnNumber % 26);
    }
};
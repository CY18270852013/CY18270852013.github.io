#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> getRow(int rowIndex)
    {
        vector<vector<int>> yanghui(rowIndex + 1);
        yanghui[0] = {1};
        for (int i = 1; i < rowIndex + 1; i++)
        {
            yanghui[i].resize(i + 1);
            yanghui[i][0] = 1;
            yanghui[i][i] = 1;
            for (int j = 1; j < i; j++)
            {
                yanghui[i][j] = yanghui[i - 1][j - 1] + yanghui[i - 1][j];
            }
        }
        return yanghui[rowIndex];
    }
};
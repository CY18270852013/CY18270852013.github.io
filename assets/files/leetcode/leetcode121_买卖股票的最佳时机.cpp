#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int minP = prices[0];
        int maxPro = 0;
        for (int i = 0; i < n; i++)
        {
            if (prices[i] < minP)
            {
                minP = prices[i];
            }
            else
            {
                if (prices[i] - minP > maxPro)
                    maxPro = prices[i] - minP;
            }
        }
        return maxPro;
    }
};
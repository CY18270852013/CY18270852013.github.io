#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        int res = 0;
        int num2 = 0;
        while (2 * num2 <= n) {
            int num1 = n - 2 * num2;
            if (num2 == 0 || num1 == 0) {
                res += 1;
            } else {
                int k = min(num1, num2);
                long temp = 1;
                for (int i = 1; i <= k; i++) {
                    temp = temp * (num1 + num2 - i + 1) / i;
                }
                res += temp;
            }
            num2++;
        }
        return res;
    }
};


int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.climbStairs(n);
}
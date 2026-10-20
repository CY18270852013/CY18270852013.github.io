#include <iostream>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        int res = 0;
        for (int i = 1; i <= x; i++) {
            if (x / i <= i && x / (i + 1) < i) {
                res = i;
                return res;
            } else if (x / i >= i && x / (i + 1) < i + 1) {
                res = i;
                return res;
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    int x;
    cin >> x;
    cout << solution.mySqrt(x);
    return 0;
}
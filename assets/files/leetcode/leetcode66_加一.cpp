#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int n = digits.size();
        for (int i = n - 1; i>= 0; i--) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            digits[i] = 0;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};

int main() {
    Solution solution;
    int n = 0;
    cin >> n;
    vector<int> digits(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> digits[i];
    }
    vector<int> expectedDigits;
    expectedDigits = solution.plusOne(digits);
    for (int i = 0; i < expectedDigits.size(); i++) {
        cout << expectedDigits[i];
        if (i < expectedDigits.size() - 1) {
            cout << ' ';
        }
    }
    return 0;
}
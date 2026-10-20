#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.length() - 1;
        int j = b.length() - 1;
        string result;
        int carry = 0; //记录要进的位数

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;

            if (i >= 0) {
                sum += (a[i] - '0');
                i--;
            }
            if (j >= 0) {
                sum += (b[j] - '0');
                j--;
            }

            result.push_back(sum % 2 + '0');
            carry = sum / 2;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution solution;
    string a, b;
    getline(cin, a);
    getline(cin, b);
    string result = solution.addBinary(a, b);
    cout << result << endl;
    return 0;
}
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == ' ' && count > 0) {
                return count;
            } else if (s[i] != ' ') {
                count++;
            }
        }
        return count;
    }
};

int main() {
    Solution solution;
    string s;
    getline(cin, s);
    cout << solution.lengthOfLastWord(s) << endl;
    return 0;
}
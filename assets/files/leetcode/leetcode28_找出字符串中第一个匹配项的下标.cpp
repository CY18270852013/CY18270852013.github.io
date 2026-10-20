#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        //构建next向量
        int lenH = haystack.length();
        int lenN = needle.length();
        vector<int> next(lenN, 0);
        for (int i = 1, j = 0; i < lenN; i++) {
            while (j > 0 && needle[i] != needle[j]) {
                j = next[j - 1];
            }
            if (needle[i] == needle[j]) {
                j++;
            }
            next[i] = j;
        }

        for (int i = 0, j = 0; i < lenH; i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j >= lenN) return i - lenN + 1;
        }
        return -1;
    }
};

int main() {
    Solution solution;
    string haystack, needle;
    getline(cin, haystack);
    getline(cin, needle);
    cout << solution.strStr(haystack, needle) << endl;

    return 0;
}
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        int n = nums.size();
        stack<int> valIndex;
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == val) {
                k++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] == val) {
                valIndex.push(i);
            }
        }
        int k1 = k;
        int i = n - 1;
        while (k1 > 0) {
            if (valIndex.top() >= n -k) {
                k1--;
                valIndex.pop();
            }
            if (valIndex.top() < n - k && nums[i] != val) {
                int temp = nums[i];
                nums[i] = val;
                nums[valIndex.top()] = temp;
                valIndex.pop();
                k1--;
            }
            i--;
        }
        return k;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int val;
    cin >> val;
    cout << solution.removeElement(nums, val) << endl;
    for (int i = 0; i < n; i++) {
        cout << nums[i];
        if (i < n - 1) {
            cout << ' ';
        }
    }

    return 0;
}
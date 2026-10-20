#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int> &nums) {
        int k = 1;
        int n = nums.size();
        int expectedNum[n];
        expectedNum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[i - 1]) {
                k++;
                expectedNum[k - 1] = nums[i];
            }
        }
        for (int j = 0; j < k; j++) {
            nums[j] = expectedNum[j];
        }

        return k;
    }
};

int main() {
    Solution solution;
    int n = 0;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int k = solution.removeDuplicates(nums);
    cout << k << endl;
    for (int j = 0; j < k; j++) {
        cout << nums[j];
        if (j < k - 1) {
            cout << ' ';
        }
    }

    return 0;
}
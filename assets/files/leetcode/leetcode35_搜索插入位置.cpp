#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= target) {
                index = i;
                return index;
            }
        }
        return nums.size();
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
    int target = 0;
    cin >> target;
    cout << solution.searchInsert(nums, target);
    return 0;
}
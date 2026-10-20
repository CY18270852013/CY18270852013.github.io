#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int n = nums.size();
        int left = 0, right = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != val) {
                nums[left] = nums[i];
                left++;
                right++;
            } else {
                right++;
            }
        }
        return left;
    }
};

int main()
{
    Solution solution;
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    int val;
    cin >> val;
    cout << solution.removeElement(nums, val) << endl;
    for (int i = 0; i < n; i++)
    {
        cout << nums[i];
        if (i < n - 1)
        {
            cout << ' ';
        }
    }

    return 0;
}
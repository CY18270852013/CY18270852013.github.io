#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        if (m == 0) {
            for (int i = 0; i < n; i++) {
                nums1[i] = nums2[i];
            }
        }
        int j = n - 1;
        for (int i = m - 1; i >= 0; i--) {
            while (j >= 0) {
                if (nums2[j] >= nums1[i]) {
                    nums1[i + j + 1] = nums2[j];
                    j--;
                } else {
                    nums1[i + j + 1] = nums1[i];
                    break;
                }
            }
        }
        if (j >= 0) {
            for (int i = 0; i <= j; i++) {
                nums1[i] = nums2[i];
            }
        }
        return;
    }
};

int main() {
    Solution solution;
    int m, n;
    cin >> m >> n;
    vector<int> nums1(m + n, 0), nums2(n, 0);
    for (int i = 0; i < m; i++) {
        cin >> nums1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> nums2[i];
    }
    solution.merge(nums1, m, nums2, n);
    for (int j = 0; j < m + n; j++) {
        cout << nums1[j];
        if (j < m + n - 1) {
            cout << ' ';
        }
    }
    return 0;
}
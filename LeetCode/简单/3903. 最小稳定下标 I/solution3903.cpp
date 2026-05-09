// https://leetcode.cn/problems/smallest-stable-index-i/

#include <bits/stdc++.h>

using namespace std;

class Solution3903 {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre_max(n);
        vector<int> suf_min(n);
        pre_max[0] = nums[0];
        for (int i = 1; i < n; i++) {
            pre_max[i] = max(pre_max[i - 1], nums[i]);
        }
        suf_min[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suf_min[i] = min(suf_min[i + 1], nums[i]);
        }
        for (int i = 0; i < n; i++) {
            if (pre_max[i] - suf_min[i] <= k) {
                return i;
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
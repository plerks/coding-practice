/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-make-array-continuous/
参考: https://leetcode.cn/problems/minimum-number-of-operations-to-make-array-continuous/solutions/1005398/on-zuo-fa-by-endlesscheng-l7yi/
标签: 【题单】滑动窗口与双指针, 正难则反, 可排序
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2009 {
public:
    /* 参考灵茶题解，
    不关心nums的原顺序，将nums排序之后考虑，最终的结果是n个连续的数，也就意味着窗口大小固定为n，
    让窗口尽量包含更多的数，那么其它数改值进来的次数就最小，注意重复的数是要放在完美操作进来的，所以要去重
    */
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int m = std::unique(nums.begin(), nums.end()) - nums.begin();
        int l = 0;
        int ans = n;
        for (int r = 0; r < m; r++) {
            while (nums[r] - nums[l] + 1 > n) l++;
            ans = min(ans, n - (r - l + 1));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2009 solu;
    cout << solu.minOperations(*new vector<int>{1,2,3,5,6}) << endl;
    return 0;
}
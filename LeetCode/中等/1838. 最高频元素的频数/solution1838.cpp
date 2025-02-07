/*
url: https://leetcode.cn/problems/frequency-of-the-most-frequent-element/description/
参考: https://leetcode.cn/problems/frequency-of-the-most-frequent-element/solutions/742719/zui-gao-pin-yuan-su-de-pin-shu-by-leetco-q5g9/
标签: 【题单】滑动窗口与双指针, 可排序
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1838 {
public:
    // 我的做法，这个问题和子序列可排序类似，把元素排序打乱不会有影响，这样就能用前缀和枚举并二分求把元素增加成nums[i]能成功多少个
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 1;
        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
        }
        for (int i = 1; i < n; i++) {
            long long x = nums[i];
            // 对于能否在k次操作内把元素全变为nums[i]的个数，从是到否变化，搜索最后一个是
            int left = 0, right = i;
            while (left <= right) {
                int mid = (left + right) / 2;
                long long cnt = x * mid - (pre[i - 1 + 1] - pre[i - mid - 1 + 1]);
                if (cnt <= k) left = mid + 1;
                else right = mid - 1;
            }
            ans = max(ans, left - 1 + 1);
        }
        return ans;
    }
    
    // 官方题解的做法，还是要先排序，不过求能变的个数用滑窗来求
    int maxFrequency_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 1;
        long long sum = 0;
        int l = 0;
        for (int r = 0; r < n; r++) {
            long long x = nums[r];
            sum += nums[r];
            while (l <= r && (r - l + 1) * x - sum > k) {
                sum -= nums[l++];
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1838 solu;
    cout << solu.maxFrequency(*new vector<int>{1,2,4}, 5) << endl;
    cout << solu.maxFrequency(*new vector<int>{100000}, 100000) << endl;

    cout << solu.maxFrequency_implementation2(*new vector<int>{1,2,4}, 5) << endl;
    cout << solu.maxFrequency_implementation2(*new vector<int>{100000}, 100000) << endl;
    return 0;
}
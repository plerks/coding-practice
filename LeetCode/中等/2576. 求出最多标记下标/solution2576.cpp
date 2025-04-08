/*
url: https://leetcode.cn/problems/find-the-maximum-number-of-marked-indices/
相关: LeetCode3048. 标记所有下标的最早秒数 I
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2576 {
public:
    // 错误的贪心，像[9,2,5,4]，2和4匹配虽然刚好，但是5不能和9匹配了。而[2 5] [4 9]则能匹配出2对
    int maxNumOfMarkedIndices_wa(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        vector<bool> vis(n);
        int r = 0;
        for (int l = 0; l < n; l++) {
            if (vis[l]) continue;
            while (r < n && (vis[r] || 2 * nums[l] > nums[r])) r++;
            if (r < n) {
                vis[l] = vis[r] = true;
                ans += 2;
            }
        }
        return ans;
    }

    /* 灵茶题解解法一，二分。这题不固定匹配对数k好像还不行，类似LeetCode3048. 标记所有下标的最早秒数 I，固定了匹配对数k之后，
    检查是否能成功是相对容易的，不用考虑到底能选多少数出来，怎么匹配。
    通过二分答案，能固定一个参数，然后检查能否合法相对容易。也就是说，固定带来了简化。
    对于选k对，一定是最小的k个数和最大的k个数匹配，并且左段最小数与右端最小数比对。注意，由于固定了k，不会出现像[9,2,5,4]
    这样，不知道2到底该和4还是和5匹配的问题。
    */
    int maxNumOfMarkedIndices(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        auto check = [&](int k) -> bool {
            for (int i = 0; i < k; i++) {
                if (2 * nums[i] > nums[n - k + i]) return false;
            }
            return true;
        };

        int left = 0, right = n / 2; 
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right * 2; // 个数要乘2
    }

    // 灵茶题解解法二，双指针，通过二分的过程可以看出，[9,2,5,4]不能让2和4匹配，必须得分左右两半。然后就能直接模拟求答案
    int maxNumOfMarkedIndices_implementation2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int i = 0, j = (n + 1) / 2; // 注意不能写成 j = n / 2，可能会导致n / 2这个数被用2次，例如[1,2,3,4,6]
        for (; j < n; j++) {
            if (2 * nums[i] <= nums[j]) i++;
        }
        return i * 2;
    }
};

int main(int argc, char const *argv[]) {
    Solution2576 solu;
    cout << solu.maxNumOfMarkedIndices(*new vector<int>{3,5,2,4}) << endl;
    cout << solu.maxNumOfMarkedIndices(*new vector<int>{9,2,5,4}) << endl;

    cout << solu.maxNumOfMarkedIndices_implementation2(*new vector<int>{1,2,3,4,6}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/description/
LeetCode参考: https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/solutions/2570598/zui-chang-di-zeng-zi-xu-lie-by-leetcode-2ipno/
              https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/solutions/2575527/qian-hou-zhui-fen-jie-zui-chang-di-zeng-9vowl/
相关: LeetCode2866. 美丽塔 II, LeetCode300. 最长递增子序列
标签: 双向dp, 双向动态规划, 最长严格递增子序列
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1671 {
public:
    // 我的解法，O(n^2)时间复杂度，通过
    int minimumMountainRemovals(const vector<int>& nums) {
        /* 和LeetCode2866. 美丽塔 II有点像，但是不一样，对dpL[i]如果找到了一个
        nums[j] < nums[i]，不一定最小删除数就是取nums[j]为nums[i]左边第一个数，
        比如[9,10,1,12]，当i为3时，找到了1 < 12，这时最优解不是1,12而是9,10,12，
        需要枚举所有左边才行。*/
        int n = nums.size();
        vector<int> dpL(n, INT_MAX); // dpL[i]表示以i为山峰，让左侧严格单增所需的最少删除数
        vector<int> dpR(n, INT_MAX);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            dpL[i] = i;
            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] >= nums[i]) continue;
                dpL[i] = min(dpL[i], dpL[j] + i - j - 1);
            }
        }
        st = {};
        for (int i = n - 1; i >= 0; i--) {
            dpR[i] = n - 1 - i;
            for (int j = i + 1; j < n; j++) {
                if (nums[j] >= nums[i]) continue;
                dpR[i] = min(dpR[i], dpR[j] + j - i - 1);
            }
        }
        int ans = INT_MAX;
        // 题目要求山峰所在的位置i满足0 < i < arr.length - 1且数组至少要有3个元素arr.length >= 3(山峰左右都要有元素)
        for (int i = 1; i < n - 1; i++) {
            if (i - dpL[i] < 1 || n - i - 1 - dpR[i] < 1) continue;
            ans = min(ans, dpL[i] + dpR[i]);
        }
        return ans;
    }

    // 官方题解解法一，使用`LeetCode300. 最长递增子序列`的动态规划解法，时间复杂度O(n^2)
    int minimumMountainRemovals_implementation2(const vector<int>& nums) {
        // 枚举i为山峰，则左侧和右侧各是一个递增子序列，求出以i结尾的左右最长递增子序列长度，再用n减去即为最小删除数
        vector<int> pre = getLISArray(nums);
        /* 这里这个{nums.rbegin(), nums.rend()}隐式转换为vector的写法头一次见，
        参考<https://blog.csdn.net/qq_38410730/article/details/105314766>，
        {nums.rbegin(), nums.rend()}是一个initializer_list，
        当用它来隐式构造vector的时候，由于vector的构造函数能直接接收initializer_list的是
        `vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())`，
        initializer_list中的T是vector装的元素类型，这里initializer_list里装的是迭代器不符合，所以编译器会把initializer_list拆开调用
        vector的构造方法，这里调用的构造方法应该是
        ```
        template<class InputIt>
        vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        ```
        也就是说C++用initializer_list初始化如果没找到匹配的构造函数还会把initializer_list拆开再尝试匹配。
        */
        vector<int> suf = getLISArray({nums.rbegin(), nums.rend()});
        reverse(suf.begin(), suf.end());
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (pre[i] > 1 && suf[i] > 1) {
                ans = max(ans, pre[i] + suf[i] - 1);
            }
        }
        return n - ans;
    }

    vector<int> getLISArray(const vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1); // dp[i]表示以nums[i]结尾的最长递增子序列长度
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return dp;
    }

    // 官方题解解法二，使用`LeetCode300. 最长递增子序列`的贪心+二分解法，时间复杂度O(nlogn)
    int minimumMountainRemovals_implementation3(const vector<int>& nums) {
        vector<int> pre = getLISArray2(nums);
        vector<int> suf = getLISArray2({nums.rbegin(), nums.rend()});
        reverse(suf.begin(), suf.end());
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (pre[i] > 1 && suf[i] > 1) {
                ans = max(ans, pre[i] + suf[i] - 1);
            }
        }
        return n - ans;
    }

    vector<int> getLISArray2(const vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1); // dp[i]表示以nums[i]结尾的最长递增子序列长度
        vector<int> d;
        for (int i = 0; i < n; i++) {
            auto it = lower_bound(d.begin(), d.end(), nums[i]); // 第一个>=nums[i]的
            if (it == d.end()) {
                d.push_back(nums[i]);
                dp[i] = d.size();
            }
            else {
                *it = nums[i];
                dp[i] = it - d.begin() + 1;
            }
        }
        return dp;
    }
};

int main(int argc, char const *argv[]) {
    Solution1671 solu;
    // cout << solu.minimumMountainRemovals({2,1,1,5,6,2,3,1}) << endl;
    // cout << solu.minimumMountainRemovals({23,47,63,72,81,99,88,55,21,33,32}) << endl;
    // cout << solu.minimumMountainRemovals({9,8,1,7,6,5,4,3,2,1}) << endl;
    cout << solu.minimumMountainRemovals({100,92,89,77,74,66,64,66,64}) << endl;
    cout << solu.minimumMountainRemovals_implementation2({100,92,89,77,74,66,64,66,64}) << endl;
    cout << solu.minimumMountainRemovals_implementation3({100,92,89,77,74,66,64,66,64}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/
参考: https://www.bilibili.com/video/BV17RwBeqErJ/
      https://leetcode.cn/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/solutions/3051552/gong-xian-fa-dan-diao-zhan-pythonjavacgo-9gz3/
相关: LeetCode3428. 最多 K 个元素的子序列的最值之和, LeetCode907. 子数组的最小值之和
标签: LeetCode第433场周赛, 贡献法, 单调栈, 子数组
*/

#include <bits/stdc++.h>

using namespace std;

// 这次周赛1题

class Solution3430 {
public:
    /* 参考灵茶题解，贡献法
    考虑以nums[i]为最小值，则左右能扩展到第一个比nums[i]大的数，nums[i]的重复元素怎么办？
    左闭右开，左边扩展到<=nums[i]的数，右边扩展到<nums[i]。这和`LeetCode3428. 最多 K 个元素的子序列的最值之和`
    排序后以每个nums[i]为左边界其实是相同的。
    l ... i ... r
    */
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        auto calc = [&]() -> long long {
            stack<int> st;
            st.push(-1); // 哨兵
            long long ans = 0;
            // 单调栈，一个元素r入栈时把所有>=自己的弹出，第一次弹出时的就是i，最后栈顶就是l。同时用了单调栈入栈和出栈的信息。
            for (int r = 0; r < nums.size(); r++) {
                while (st.size() > 1 && nums[st.top()] >= nums[r]) {
                    int i = st.top(); // 找到i
                    int x = nums[i];
                    st.pop();
                    int l = st.top(); // i下面的是l
                    if (r - l - 1 <= k) {
                        ans += (long long)x * (i - l) * (r - i);
                    }
                    else {
                        // i位置必须选，(l, i)合法，(i, r)合法，还有个子数组长度不能>k的限制
                        int L = max(l, i - k);
                        int R = min(r, i + k);
                        /* 左边i - L - 1个元素，右边R - i - 1个元素，窗口长度>k的情况下，无论是左边偏长
                        还是右边偏长，窗口移动过程中都会出现两种情况，
                        当窗口(长固定为k)还未到达右边界之前(一定存在这种情况)，
                        右边不能全选，左端点在L+1，右边可从(i, k+L+1)中选，有 k+L-i 种情况
                                    ...
                                    左端点在R-k，右边可从(i, R)种选，有 R - i 种情况
                        求和为(k+L+R-2i+1)(R-k-L)/2
                        当窗口到达右边界(一定存在这种情况)，右边都是可以全选的，一共(i-(R-k))(R-i)种情况
                        */
                        long long cnt1 = (k + L + R - 2 * i + 1) * (R - k - L) / 2;
                        long long cnt2 = (i - (R - k)) * (R - i);
                        ans += x * (cnt1 + cnt2);
                    }
                }
                st.push(r);
            }
            return ans;
        };

        nums.push_back(INT_MIN / 2); // 哨兵，把最后栈中还存在的所有元素弹出
        long long ans = calc();
        for (int &x : nums) x = -x; // 把所有元素取反，这样求最大值的贡献仍然可以用求最小值的贡献的代码
        nums.back() = -nums.back(); // 末尾元素仍然要是负无穷
        ans -= calc();
        return ans;
    }

    // 灵茶题解中还有一种计算 包含i，长度<=k的子数组个数 的方法，就是区间内<=k的子数组个数 - 左侧<=k的子数组个数 - 右侧<=k的子数组个数
};

int main(int argc, char const *argv[]) {
    Solution3430 solu;
    cout << solu.minMaxSubarraySum(*new vector<int>{1,2,3}, 2) << endl;
    return 0;
}
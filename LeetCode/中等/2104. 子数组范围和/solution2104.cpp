/*
url: https://leetcode.cn/problems/sum-of-subarray-ranges/
参考: https://leetcode.cn/problems/sum-of-subarray-ranges/solutions/1153054/cong-on2-dao-ondan-diao-zhan-ji-suan-mei-o1op/
标签: 【算法题单】单调栈, 贡献法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2104 {
public:
    /* 参考灵茶题解，
    计算nums[i]作为最小值能出现在几个子数组中，即找左侧第一个 < nums[i]的位置，和右侧第一个 <= nums[i]的位置。对相等元素，左开右闭，不重不漏。
    计算nums[i]作为最大值，即找左侧第一个 >，和右侧第一个 >=
    这里的关键点在于可以放心地把 最大 - 最小 分开成独立的两个，如果去考虑最大和最小所在的数组，就没法做
    */
    long long subArrayRanges(vector<int>& nums) {
        long long ans = f(nums);
        for (int& x : nums) x = -x;
        ans += f(nums); // 把nums取反，然后求最小值的贡献，即为最大值的贡献。复用代码
        return ans;
    }

    // 求最小值的贡献
    long long f(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        stack<int> st;
        vector<int> left(n, -1);
        vector<int> right(n, n);
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        for (int i = 0; i < n; i++) {
            ans += -(right[i] - i) * 1LL * (i - left[i]) * 1LL * nums[i]; // 最小值是负贡献，定义里是 - min
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2104 solu;
    cout << solu.subArrayRanges(*new vector<int>{1,2,3}) << endl;
    cout << solu.subArrayRanges(*new vector<int>{1,3,3}) << endl;
    cout << solu.subArrayRanges(*new vector<int>{4,-2,-3,4,1}) << endl;
    return 0;
}
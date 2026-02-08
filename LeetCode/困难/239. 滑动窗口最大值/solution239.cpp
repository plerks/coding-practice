/*
url: https://leetcode.cn/problems/sliding-window-maximum/
相关: LeetCode1438. 绝对差不超过限制的最长连续子数组, LeetCode3835. 开销小于等于 K 的子数组数目
*/

#include <bits/stdc++.h>

using namespace std;

class Solution239 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n - k + 1);
        deque<int> dq; // 双端队列，从左往右单减
        for (int l = 0, r = 0; r < n; r++) {
            /* 入尾，注意r必须从尾部往前排除比自己小的元素，而不是从头部往后排除。例如，deque现在数字是[1 5 2 2]，要进来一个3，把1排出
            后，后面窗口滑动，5出去，到了[2 2 3]时，会认为2是当前最大值，而实际应当是3。
            */
            while (!dq.empty() && nums[dq.back()] <= nums[r]) dq.pop_back();
            dq.push_back(r);
            if (r >= k - 1) {
                // 出头，获取最大值时先排出头部过时元素
                while (dq.front() < l) dq.pop_front();
                ans[l] = nums[dq.front()];
                l++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution239 solu;
    // auto a = solu.maxSlidingWindow(*new vector<int>{1,3,-1,-3,5,3,6,7}, 3);
    auto b = solu.maxSlidingWindow(*new vector<int>{1,3,1,2,0,5}, 3);
    return 0;
}
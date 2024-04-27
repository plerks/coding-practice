/*
url: https://leetcode.cn/problems/next-greater-element-iv/description/
LeetCode参考: https://leetcode.cn/problems/next-greater-element-iv/solutions/2562064/xia-yi-ge-geng-da-yuan-su-iv-by-leetcode-hjqv/
相关: LeetCode84. 柱状图中最大的矩形
标签: 单调栈出栈元素性质, 单调栈 + 优先队列, 双单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2454 {
public:
    // 官方题解解法一，单调栈 + 优先队列
    /* 用一个单调递减栈，类似`LeetCode84. 柱状图中最大的矩形`，考虑单调栈元素弹出时的规律，当遍历到nums[i]时，对于弹出的元素nums[j]...，
    其比nums[i]小，则nums[i]是这些元素的右一大(右边第一个比自己大的)。当nums[i]被弹出时，这时的nums[k]是这些nums[j]的右二大。
    但是此时num[j]已被弹出，因此需要用一个优先队列暂存nums[j]...这些已经发现了右一大的元素，这样就能知道这些nums[j]的右二大 */
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> ans(n, -1);
        // std::greater是一个模板类，其中定义的方法为返回两个对象x, y，是否x > y
        // pair存nums中元素的值与位置
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 这里pq应该可以简化为只存int，存nums中元素下标
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            // 这两个while循环的顺序不能反
            while (!pq.empty() && num > pq.top().first) {
                // pq里的元素已经找到了右一大，因此若num > pq.top()，则num就是pq.top()的右二大
                ans[pq.top().second] = num;
                pq.pop();
            }
            while (!st.empty() && num > nums[st.top()]) {
                // st.top()找到了右一大为num
                int j = st.top();
                st.pop();
                pq.push(make_pair(nums[j], j));
            }
            st.push(i);
        }
        return ans;
    }

    // 官方题解解法二，双单调栈，用另一个单调递减栈替代上一种解法中的最小堆
    vector<int> secondGreaterElement_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<int> st1;
        vector<int> st2;
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            while (!st2.empty() && num > nums[st2.back()]) {
                ans[st2.back()] = num;
                st2.pop_back();
            }
            int pos = st1.size() - 1;
            // st1中这些要弹出的元素原本是按单减排的
            while (pos >= 0 && num > nums[st1[pos]]) {
                pos--;
            }
            st2.insert(st2.end(), st1.begin() + (pos + 1), st1.end());
            st1.resize(pos + 1);
            st1.push_back(i);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2454 solu;
    vector<int> nums = {2,4,0,9,6};
    solu.secondGreaterElement(nums);
    solu.secondGreaterElement_implementation2(nums);
    return 0;
}

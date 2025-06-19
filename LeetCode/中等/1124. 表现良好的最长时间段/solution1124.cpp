/*
url: https://leetcode.cn/problems/next-greater-element-i/
参考: https://leetcode.cn/problems/longest-well-performing-interval/solutions/2110211/liang-chong-zuo-fa-liang-zhang-tu-miao-d-hysl/
相关: LeetCode962. 最大宽度坡
标签: 【算法题单】单调栈, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1124 {
public:
    /* 灵茶题解解法一，hours[i] > 8的相当于1，< 8的相当于-1。要找区间和 > 0的最长区间。
    先计算前缀和，则区间和为端点前缀和之差，于是区间和 > 0变成右端点前缀和 > 最端点前缀和。
    即最长(i, j)，这变成了LeetCode962. 最大宽度坡。
    */
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i - 1 + 1] + (hours[i] > 8 ? 1 : -1);

        // 找最长的(i, j)，使得pre[i] < pre[j]
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (st.empty() || pre[i] < pre[st.top()]) st.push(i);
        }
        int ans = 0;
        for (int j = n - 1; j >= 0; j--) {
            // [st.top(), j]的前缀和 > 0，即 pre[j] > pre[st.top() - 1]
            while (!st.empty() && pre[st.top() - 1 + 1] < pre[j + 1]) {
                ans = max(ans, j - st.top() + 1);
                st.pop();
            }
        }
        return ans;
    }

    /* 灵茶题解解法二，一次遍历的写法，利用前缀和的连续性
    hours的元素相当于只有1和-1，
    考虑要找的[i, j]，若pre[j] > 0，则直接取i为0，即取整个前端
    若pre[j] <= 0，则找pre[j] - 1 (小于0)第一次出现的位置，为什么不找左边可能出现更小的值？
    神奇的来了，因为要出现pre[j] - 2，则由于连续性，0到pre[j] - 2之间一定出现了pre[j] - 1，有pre[j] - 1在更左边
    */
    int longestWPI_implementation2(vector<int>& hours) {
        int n = hours.size();
        vector<int> pre(n);
        pre[0] = hours[0] > 8 ? 1 : -1;
        for (int i = 1; i < n; i++) pre[i] = pre[i - 1] + (hours[i] > 8 ? 1 : -1);

        int map[n + 2]; // map[i]存前缀和里-i第一次出现的位置，最大出现-n，然后可能要找 -n - 1的位置，所以map要n + 2长
        fill(map, map + n + 2, -1);
        int ans = 0;
        for (int j = 0; j < n; j++) {
            if (pre[j] > 0) {
                ans = max(ans, j + 1);
            }
            else {
                if (map[-(pre[j] - 1)] >= 0) { // 有pre[j] - 1，对于区间为[pos_of(pre[j] - 1) + 1, j]
                    ans = max(ans, j - map[-(pre[j] - 1)]);
                }
                if (map[-pre[j]] < 0) { // 更新map
                    map[-pre[j]] = j;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1124 solu;
    // cout << solu.longestWPI(*new vector<int>{9,9,6,0,6,6,9}) << endl;
    // cout << solu.longestWPI(*new vector<int>{6,9,9}) << endl;
    cout << solu.longestWPI(*new vector<int>{6,6,9}) << endl;

    // cout << solu.longestWPI_implementation2(*new vector<int>{6,6,9}) << endl;
    cout << solu.longestWPI_implementation2(*new vector<int>{6,9,6}) << endl;
    return 0;
}
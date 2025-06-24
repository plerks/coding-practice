/*
url: https://leetcode.cn/problems/find-the-most-competitive-subsequence/
参考: https://leetcode.cn/problems/find-the-most-competitive-subsequence/solutions/2788312/gen-zhao-wo-guo-yi-bian-shi-li-2ni-jiu-m-36c4/
相关: LeetCode321. 拼接最大数, LeetCode2030. 含特定字母的最小子序列
标签: 【算法题单】单调栈, 字典序
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1673 {
public:
    // 我的解法
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> right(n); // 右侧第一个 < 自己的位置
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (k <= 0) break;
            // 如果右侧有 < 自己的，且那个位置够选出k个，那么i不选。否则i要选
            if (right[i] != n && n - right[i] >= k) continue;
            else {
                ans.push_back(nums[i]);
                k--;
            }
        }
        return ans;
    }

    // 灵茶题解解法，更简短
    // nums[i]入栈，其能把栈中已有的 > 自己的元素都出来，以获得更小的字典序。出栈时若元素不够了要提前停止
    vector<int> mostCompetitive_implmentation2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back() > nums[i] && st.size() - 1 + n - i >= k) st.pop_back();
            if (st.size() < k) st.push_back(nums[i]);
        }
        return st;
    }
};

int main(int argc, char const *argv[]) {
    Solution1673 solu;
    auto a = solu.mostCompetitive(*new vector<int>{3,5,2,6}, 2);

    auto b = solu.mostCompetitive(*new vector<int>{2,4,3,3,5,4,9,6}, 4);
    return 0;
}
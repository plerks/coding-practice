/*
url: https://leetcode.cn/problems/beautiful-towers-ii/description/
相关: LeetCode2865. 美丽塔 I
标签: 单调栈, 双向dp, 双向动态规划
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2866 {
public:
    // 暴力法，778 / 785 个通过的测试用例，超时
    long long maximumSumOfHeights_exceed_time_limit(vector<int>& maxHeights) {
        // 枚举山峰的每个位置，山峰应该取maxHeights，对于山峰左右，其应该取min(heights[i +/- 1], maxHeights[i])
        int n = maxHeights.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long max = 0;
            max += maxHeights[i];
            int pre = maxHeights[i];
            for (int j = i - 1; j >= 0; j--) {
                long long height = min(pre, maxHeights[j]);
                max += height;
                pre = height;
            }
            pre = maxHeights[i];
            for (int j = i + 1; j < n; j++) {
                long long height = min(pre, maxHeights[j]);
                max += height;
                pre = height;
            }
            ans = std::max(ans, max); // 定义了个变量max，这里得写std::max指明是要用max()函数
        }
        return ans;
    }

    // 一个错误想法：最优方案一定在峰顶在maxHeights取最大值的位置取得，[6,5,2,1,5,4,4,2]这个用例，最优解的峰顶在index == 4的位置
    long long maximumSumOfHeights_wrong(const vector<int>& maxHeights) {
        int n = maxHeights.size();
        int mx = *max_element(maxHeights.begin(), maxHeights.end());
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (maxHeights[i] == mx) {
                long long sum = 0;
                sum += maxHeights[i];
                int pre = maxHeights[i];
                for (int j = i - 1; j >= 0; j--) {
                    long long height = min(pre, maxHeights[j]);
                    sum += height;
                    pre = height;
                }
                pre = maxHeights[i];
                for (int j = i + 1; j < n; j++) {
                    long long height = min(pre, maxHeights[j]);
                    sum += height;
                    pre = height;
                }
                ans = max(ans, sum);
            }
        }
        return ans;
    }

    long long maximumSumOfHeights(const vector<int>& maxHeights) {
        // 用单调栈，分别求以maxHeights[i]为峰顶时，左侧和右侧的最大和
        int n = maxHeights.size();
        vector<long long> dpL(n, 0);
        vector<long long> dpR(n, 0);
        stack<int> st;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            /* 对于maxHeights[i]为峰顶，若st.top() <= maxHeights[i]，则dpL[i]为dpL[i - 1] + maxHeights[i]，
            否则要找到第一个<= maxHeights[i]的位置x，dpL[i]为子问题dpL[x]加上中间部分的。 */
            while (!st.empty() && maxHeights[st.top()] > maxHeights[i]) {
                st.pop();
            }
            int left = st.empty() ? -1 : st.top();
            dpL[i] = (left == -1 ? 0 : dpL[left]) + (long long)(i - left) * maxHeights[i];
            st.push(i);
        }
        st = {}; // 清空stack，C++的stack没clear()方法
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && maxHeights[st.top()] > maxHeights[i]) {
                st.pop();
            }
            int right = st.empty() ? n : st.top();
            dpR[i] = (right == n ? 0 : dpR[right]) + (long long)(right - i) * maxHeights[i];
            st.push(i);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dpL[i] + dpR[i] - maxHeights[i]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2866 solu;
    cout << solu.maximumSumOfHeights_wrong({6,5,2,1,5,4,4,2}) << endl;
    cout << solu.maximumSumOfHeights({6,5,2,1,5,4,4,2}) << endl;
    cout << solu.maximumSumOfHeights({5,3,4,1,1}) << endl;
    return 0;
}
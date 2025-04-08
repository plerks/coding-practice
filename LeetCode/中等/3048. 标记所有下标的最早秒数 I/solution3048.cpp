/*
url: https://leetcode.cn/problems/earliest-second-to-mark-indices-i/
相关: LeetCode2576. 求出最多标记下标
标签: 【题单】二分算法, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3048 {
public:
    // 我的解法，用时7ms
    // 通过二分答案，规避了寻找最优方案的策略选择问题，而是转化为了用一个固定时间能否完成的问题
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();

        auto check = [&](int t) -> bool { // 检查从changeIndices[0, t - 1]能否标记完nums
            vector<int> ddl(n, -1); // 每朵花在[0, t - 1]的截止日期
            for (int i = 0; i <= t - 1; i++) {
                ddl[changeIndices[i] - 1] = i;
            }
            for (int i = 0; i < n; i++) if (ddl[i] == -1) return false;
            auto comp = [&](int x, int y) {
                return ddl[x] > ddl[y];
            };
            priority_queue<int, vector<int>, decltype(comp)> q(comp);
            for (int i = 0; i < n; i++) q.push(i);

            vector<int> remain = nums;
            int cnt = 0; // 能被标记的数量
            for (int i = 0; i <= t - 1; i++) {
                int index = changeIndices[i] - 1;
                if (i == ddl[index]) {
                    if (remain[index] != 0) return false;
                    else cnt++;
                }
                else {
                    // 优先减小离截止日期最近的
                    while (!q.empty() && remain[q.top()] == 0) q.pop();
                    if (!q.empty()) remain[q.top()]--;
                }
            }
            return cnt == n;
        };

        int left = 1, right = m;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left == m + 1 ? -1 : left;
    }

    /* 灵茶题解的check思路，不需要用一个优先队列模拟，如果当天是ddl，则使用存储的减小机会检查nums是否能变为0，如果不是ddl，
    则把减小的次数储存起来，等到遇到ddl时再使用。用时3ms
    */
    int earliestSecondToMarkIndices_implementation2(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();

        auto check = [&](int t) -> bool { // 检查从changeIndices[0, t - 1]能否标记完nums
            vector<int> ddl(n, -1); // 每朵花在[0, t - 1]的截止日期
            for (int i = 0; i <= t - 1; i++) {
                ddl[changeIndices[i] - 1] = i;
            }
            for (int i = 0; i < n; i++) if (ddl[i] == -1) return false;

            int cnt = 0; // 暂存的减小次数
            for (int i = 0; i <= t - 1; i++) {
                if (ddl[changeIndices[i] - 1] == i) { // ddl，用存储的量
                    int index = changeIndices[i] - 1;
                    if (nums[index] > cnt) return false;
                    else cnt -= nums[index];
                }
                else cnt++;
            }
            return true;
        };

        int left = n, right = m; // 就算原本nums[i]全为0，每天标记一个，也需n天
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left >= m + 1 ? -1 : left; // 要写left >= m + 1而非left == m + 1，区间[n, m]，可能一开始n就比m大
    }

    /* 灵茶题解解法二，倒序遍历，初始化ddl的个数cnt = n，每遇到一个ddl，加上这个项目需要的减小次数到require里，而不是ddl，则
    可以将require - 1，最后cnt为0且require为0则说明按要求完成了所有减小次数。用时0ms
    */
    int earliestSecondToMarkIndices_implementation3(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();

        vector<int> visited(n);
        auto check = [&](int t) -> bool { // 检查从changeIndices[0, t - 1]能否标记完nums
            int cnt = n, require = 0;
            for (int i = t - 1; i >= 0 && require <= i + 1; i--) { // 最多i + 1天做工作，require > i + 1时一定完不成
                int index = changeIndices[i] - 1;
                if (visited[index] != t) {
                    /* 这里非常特别[special]，这里的本意是想要在每次二分时，检查当前位置i是否是[0, t - 1]的ddl位置，
                    这可以预先遍历一遍获得ddl位置。也可以用一个visited数组，初始化全为false，然后倒序遍历的过程中，第一次遇到
                    则标记为true。
                    但是这里特殊的是：每次check，visited不需要重新初始化，难道不会受脏数据影响吗？
                    不会，注意，每次二分，t是各不相同的，因此visited[i]置为t就相当于一个特异化的"true"，
                    当且仅当此次check已经访问过了这个index的ddl，visited[index]才会为t，所以不需要重新初始化visited。
                    且n >= 1，t不会为0，因此最开始visited全0就行。
                    */
                    visited[index] = t;
                    cnt--; // 直接完成
                    require += nums[index]; // 累积完成所需天数
                }
                else if (require > 0) require--; // 当前有工作可做，做一天工作
            }
            return cnt == 0 && require == 0;
        };

        int left = n, right = m; // 就算原本nums[i]全为0，每天标记一个，也需n天
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left >= m + 1 ? -1 : left; // 要写left >= m + 1而非left == m + 1，区间[n, m]，可能一开始n就比m大
    }
};

int main(int argc, char const *argv[]) {
    Solution3048 solu;
    cout << solu.earliestSecondToMarkIndices(*new vector<int>{2,2,0}, *new vector<int>{2,2,2,2,3,2,2,1}) << endl;

    cout << solu.earliestSecondToMarkIndices_implementation2(*new vector<int>{2,2,0}, *new vector<int>{2,2,2,2,3,2,2,1}) << endl;
    cout << solu.earliestSecondToMarkIndices_implementation2(*new vector<int>{0,1,3}, *new vector<int>{2}) << endl;

    cout << solu.earliestSecondToMarkIndices_implementation3(*new vector<int>{2,2,0}, *new vector<int>{2,2,2,2,3,2,2,1}) << endl;
    return 0;
}
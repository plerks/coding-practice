/*
url: https://leetcode.cn/problems/maximum-capacity-within-budget/
参考: https://leetcode.cn/problems/maximum-capacity-within-budget/solutions/3883296/pai-xu-qian-zhui-zui-da-zhi-dan-diao-zha-zz22/
标签: LeetCode第485场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3814 {
public:
    // 周赛时的做法，用双指针
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        int ans = 0;
        for (int i = 0; i < n; i++) { // 只选一台
            if (costs[i] < budget) ans = max(ans, capacity[i]);
        }
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {costs[i], capacity[i]};
        }
        sort(arr.begin(), arr.end());
        vector<int> pre_max(n + 1);
        for (int i = 0; i < n; i++) {
            pre_max[i + 1] = max(pre_max[i], arr[i].second);
        }
        for (int l = 0, r = n - 1; r >= 0; r--) {
            while (r > l && arr[l].first + arr[r].first < budget) {
                l++;
            }
            if (l - 1 >= 0) ans = max(ans, pre_max[min(l - 1, r - 1) + 1] + arr[r].second);
        }
        return ans;
    }

    // 简化一下，只选一台的情况可以合并，不用特别考虑
    int maxCapacity_implementation2(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        int ans = 0;
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {costs[i], capacity[i]};
        }
        sort(arr.begin(), arr.end());
        vector<int> pre_max(n + 1);
        for (int i = 0; i < n; i++) {
            pre_max[i + 1] = max(pre_max[i], arr[i].second);
        }
        for (int l = 0, r = n - 1; r >= 0; r--) {
            while (r > l && arr[l].first + arr[r].first < budget) {
                l++;
            }
            if (arr[r].first < budget) ans = max(ans, pre_max[min(l - 1, r - 1) + 1] + arr[r].second); // 顺便就把只选一台的情况包括了
        }
        return ans;
    }

    // 灵茶题解里的单调栈做法，时间复杂度也是 O(n)，不过不用前缀最大值
    // 枚举右，维护左，排序之后，单调栈顶放capacity最大的，一旦对于一个右，栈顶cost太大，对更右的右也会太大，栈中元素没用了，从而符合单调栈的特性
    // 此外，由于cost已经单增排序，因此可以再把栈中capacity维护成单增的，只有capacity更大才值得入栈
    // 这样就能把栈顶维护成对于当前的'右'的最优选'左'
    // 虽说是单调栈，但是和最原始的单调栈有所不同
    // 每个点进出栈一次，因此时间复杂度为 O(n)
    int maxCapacity_implementation3(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        int ans = 0;
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {costs[i], capacity[i]};
        }
        sort(arr.begin(), arr.end());
        stack<pair<int, int>> st;
        for (int i = 0; i < n; i++) {
            if (arr[i].first >= budget) continue;
            while (!st.empty() && st.top().first + arr[i].first >= budget) st.pop();
            ans = max(ans, arr[i].second + (st.empty() ? 0 : st.top().second));
            if (st.empty() || arr[i].second > st.top().second) st.push(arr[i]); // cost已经是单增排序的了，只有capacity更大才有价值入栈
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3814 solu;
    // cout << solu.maxCapacity_implementation3(*new vector<int>{4, 6}, *new vector<int>{5, 3}, 3) << endl;
    cout << solu.maxCapacity_implementation3(*new vector<int>{2, 2, 2}, *new vector<int>{3, 5, 4}, 5) << endl;
    return 0;
}
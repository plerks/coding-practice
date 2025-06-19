/*
url: https://leetcode.cn/problems/car-fleet-ii/
参考: https://leetcode.cn/problems/car-fleet-ii/solutions/625661/che-dui-ii-si-lu-tui-dao-zhan-de-ying-yo-jqym/
相关: LeetCode853. 车队
标签: 【算法题单】单调栈, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1776 {
public:
    // 参考题解
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        const double inf = std::numeric_limits<double>::max();
        vector<double> ans(n, inf);
        stack<int> st; // 单调栈
        /* 前面慢的车会把后面的车挡住，考虑现在计算中间某辆车x的追及时间，其右边有多辆车，
        x到底与谁合并要看：
            1. 追不追得上右侧的车，如果追不上，那栈顶的可以pop，后面都会被x这辆慢车挡住
            2. 右侧的车也可能发生合并，是x先追上还是右侧车先合并？（右侧还可能发生多次合并）
                如果y先与z合并，则y也要pop，现在要根据z计算x

        一辆快车 y 可能被右侧的 z p q ... 多辆慢车多次减速，所以要把他们都存在栈中，到了
        x时，才知道到底x与哪辆车相遇。
        假设 x 要等到 y 被 p 减速之后才能追到，那中间出栈的元素 y z 会不会对后续的计算产生影响？
        不会，x 再左边的元素不会快过 x，它们也一定追不上 y z。而是和 x 一样追上 q（指追上被q合并的 z p q）

        x导致的出栈的目的是，找到自己能追上的第一辆车(指不经过缓速的，缓速后，快车被等价为自己追上的慢车)
        */
        for (int i = n - 1; i >= 0; i--) {
            // 追不上的出栈，或者i只能追上被缓速后的车（i无法在栈顶车被缓速前追上栈顶车），那么也出栈，追的相当于是更前面的慢车
            while (true) {
                if (st.empty()) break;
                int d = cars[st.top()][0] - cars[i][0];
                if (cars[i][1] <= cars[st.top()][1] || d / (double)(cars[i][1] - cars[st.top()][1]) > ans[st.top()]) {
                    st.pop();
                }
                else break;
            }
            if (st.empty()) ans[i] = inf;
            else ans[i] = (cars[st.top()][0] - cars[i][0]) / (double)(cars[i][1] - cars[st.top()][1]);
            st.push(i);
        }
        for (double &t : ans) {
            if (t == inf) t = -1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1776 solu;
    auto a = solu.getCollisionTimes(*new vector<vector<int>>{{1,2},{2,1},{4,3},{7,2}});
    auto b = solu.getCollisionTimes(*new vector<vector<int>>{{3,4},{5,4},{6,3},{9,1}});
    auto c = solu.getCollisionTimes(*new vector<vector<int>>{{1,2},{3,4},{7,3},{8,2},{10,1},{11,5},{12,1},{15,3},{16,3},{19,4}});
    return 0;
}
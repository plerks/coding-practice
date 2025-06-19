/*
url: https://leetcode.cn/problems/steps-to-make-array-non-decreasing/
标签: 【算法题单】单调栈, [mark]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2289 {
public:
    /* 参考灵茶题解，用[10,1,2,3,4,5,6,1,2,3]这个用例来看，结果来说删得最后只剩10，但是答案不是9而是6，因为6可以同步删1 2 3。
    求每个点得删除时刻。
    如果一个单增的片段要被删，删除时刻才是单增+1的。
    像6 1 2 3，则3的删除时刻为3，但是像1 2 3，3就不需删除，关键点在这个6上。
    而像6 5 4 3这样，可以同步删除，注意3的删除时刻是1，不是3。一个元素是因左侧第一个 > 自己 的元素而被删除的
    */
    int totalSteps(vector<int>& nums) {
        int ans = 0;
        stack<pair<int, int>> st; // (值, 删除时刻) 栈的值单减
        for (int x : nums) {
            // 找x左侧第一个 > x 的元素。如果不存在，则x不需删除；如果存在，则把中间删完了就轮到x删除
            int cand_time = 0;
            while (!st.empty() && st.top().first <= x) {
                /* 注意这里不能写成 if (cand_time == 0) cand_time = st.top().second; 也就是说不能取第一次栈顶的那个删除时刻，
                [5,14,15,2,11,5,13,15]这个用例可以看出来，栈中删除时刻不一定是栈顶的最大，15,2,11,5 到 13 入栈时，15 11 5 的删除时刻
                分别是 0 2 1。
                13左侧第一个比自己大的元素是15，要把中间的删完，然后删13，所以要求中间段的最大值
                */
                cand_time = max(cand_time, st.top().second);
                st.pop();
            }
            int delete_time = st.empty() ? 0 : cand_time + 1;
            ans = max(ans, delete_time);
            st.push({x, delete_time});
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2289 solu;
    // cout << solu.totalSteps(*new vector<int>{5,3,4,4,7,3,6,11,8,5,11}) << endl;
    // cout << solu.totalSteps(*new vector<int>{10,1,2,3,4,5,6,1,2,3}) << endl;
    cout << solu.totalSteps(*new vector<int>{5,14,15,2,11,5,13,15}) << endl;
    cout << solu.totalSteps(*new vector<int>{7,14,4,14,13,2,6,13}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/maximum-profit-in-job-scheduling/
参考: https://leetcode.cn/problems/maximum-profit-in-job-scheduling/solutions/1913089/dong-tai-gui-hua-er-fen-cha-zhao-you-hua-zkcg/
相关: LeetCode3414. 不重叠区间的最大得分
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1235 {
public:
    /* 题解是按结束时间排序然后做的，这里按开始时间排序去做。
    假设第一个选了job[x]，那么下一个选的job的开始时间必须>=x的结束时间，由此可以考虑dp方式。
    按开始时间排序后，考虑对jobs[i, n-1]，若不选择job[i]，则f[i] = f[i + 1],
    若选择job[i]，则f[i] = profit[i] + f[j]，j为第一个开始时间 >= endTime[i] 的任务
    f[i] = max(f[i + 1], profit[i] + f[j])
    */
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; i++) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }

        sort(jobs.begin(), jobs.end());

        vector<int> f(n + 1);

        int ans = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int j = lower_bound(jobs.begin(), jobs.end(), vector<int>{jobs[i][1], INT_MIN, INT_MIN}) - jobs.begin();
            f[i] = max(f[i + 1], jobs[i][2] + f[j]);
            ans = max(ans, f[i]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1235 solu;
    cout << solu.jobScheduling(*new vector<int>{1,2,3,3}, *new vector<int>{3,4,5,6}, *new vector<int>{50,10,40,70}) << endl;
    cout << solu.jobScheduling(*new vector<int>{4,2,4,8,2}, *new vector<int>{5,5,5,10,8}, *new vector<int>{1,2,8,10,4}) << endl;
    return 0;
}
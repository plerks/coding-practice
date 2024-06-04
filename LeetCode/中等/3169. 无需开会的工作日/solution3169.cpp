/*
url: https://leetcode.cn/problems/count-days-without-meetings/description/
相关: LeetCode56. 合并区间
标签: LeetCode第400场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3169 {
public:
    // 周赛时的解法，通过，把区间合并算总天数
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end(), [](vector<int>& x, vector<int>& y) {
            if (x[0] < y[0]) return true;
            return false;
        });
        vector<vector<int>> intervals;
        int left = meetings[0][0];
        int right = meetings[0][1];
        for (int i = 1; i < meetings.size(); i++) {
            auto &myInterval = meetings[i];
            if (myInterval[0] > right) {
                intervals.push_back({left, right});
                left = myInterval[0];
                right = myInterval[1];
            }
            else {
                right = max(right, myInterval[1]);
            }
        }
        intervals.push_back({left, right});
        int count = 0;
        for (auto &m : intervals) {
            count += m[1] - m[0] + 1;
        }
        return days - count;
    }
};

int main(int argc, char const *argv[]) {
    Solution3169 solu;
    vector<vector<int>> meetings = {{5,7},{1,3},{9,10}};
    cout << solu.countDays(10, meetings) << endl;
    return 0;
}

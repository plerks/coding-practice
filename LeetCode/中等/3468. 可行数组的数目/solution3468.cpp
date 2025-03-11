/*
url: https://leetcode.cn/problems/find-the-number-of-copy-arrays/
参考: https://www.bilibili.com/video/BV1m39bYiEVV/
标签: LeetCode第151场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3468 {
public:
    // 周赛时的做法，通过。中间差相同，则序列值取决于头，用n个范围来求第一个元素的范围。
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        int n = original.size();
        vector<long long> diff(n - 1);
        for (int i = 0; i < n - 1; i++) {
            diff[i] = original[i + 1] - original[i];
        }
        vector<long long> pre(n - 1);
        pre[0] = diff[0];
        for (int i = 1; i < n - 1; i++) {
            pre[i] = pre[i - 1] + diff[i];
        }

        long long l = bounds[0][0], r = bounds[0][1];
        for (int i = 0; i < n - 1; i++) {
            l = max(l, bounds[i + 1][0] - pre[i]);
            r = min(r, bounds[i + 1][1] - pre[i]);
        }

        return r - l + 1 <= 0 ? 0 : r - l + 1;
    }

    // 参考灵茶题解，countArrays()先求差分再求前缀和，就是变回了original
    int countArrays_implementation2(vector<int>& original, vector<vector<int>>& bounds) {
        int n = original.size();

        long long l = bounds[0][0], r = bounds[0][1];
        for (int i = 1; i < n; i++) {
            l = max(l, (long long)bounds[i][0] - (original[i] - original[0]));
            r = min(r, (long long)bounds[i][1] - (original[i] - original[0]));
        }

        return r - l + 1 <= 0 ? 0 : r - l + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3468 solu;
    cout << solu.countArrays_implementation2(*new vector<int>{1,2,3,4}, *new vector<vector<int>>{{1,2},{2,3},{3,4},{4,5}}) << endl;
    return 0;
}
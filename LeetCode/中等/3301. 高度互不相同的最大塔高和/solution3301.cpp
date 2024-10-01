/*
url: https://leetcode.cn/problems/maximize-the-total-height-of-unique-towers/description/
标签: LeetCode第140场双周赛, 贪心
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3301 {
public:
    // 周赛时的写法，通过
    long long maximumTotalSum(vector<int>& maximumHeight) {
        priority_queue<int, vector<int>, less<int>> q;
        for (int h : maximumHeight) q.push(h);
        int last = q.top();
        q.pop();
        long long ans = last;
        while (!q.empty()) {
            int h = q.top();
            q.pop();
            int candidate = min(h, last - 1);
            if (candidate <= 0) return -1;
            ans += candidate;
            last = candidate;
        }
        return ans;
    }

    // 理一下重新写
    long long maximumTotalSum_implementation2(vector<int>& maximumHeight) {
        sort(maximumHeight.rbegin(), maximumHeight.rend());
        long long ans = maximumHeight[0];
        for (int i = 1; i < maximumHeight.size(); i++) {
            maximumHeight[i] = min(maximumHeight[i - 1] - 1, maximumHeight[i]);
            if (maximumHeight[i] == 0) return -1;
            ans += maximumHeight[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

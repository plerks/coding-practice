/*
url: https://leetcode.cn/problems/minimum-time-to-make-rope-colorful/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1578 {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int ans = 0;
        for (int i = 0; i < n;) {
            int start = i;
            int mx = neededTime[start];
            int sum = neededTime[start];
            for (i++; i < n && colors[i] == colors[i - 1]; i++) {
                mx = max(mx, neededTime[i]);
                sum += neededTime[i];
            }
            ans += sum - mx;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1578 solu;
    cout << solu.minCost("abaac", *new vector<int>{1,2,3,4,5}) << endl;
    return 0;
}
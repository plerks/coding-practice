/*
url: https://leetcode.cn/problems/maximum-consecutive-floors-without-special-floors/?envType=daily-question&envId=2025-01-06
相关: 典型问题/到最近的x的最大距离
*/

#include <bits/stdc++.h>

using namespace std;

/* 这题和`典型问题/到最近的x的最大距离`情景有点像，但是这题1 <= bottom <= special[i] <= top <= 10^9，区间过长，dp会超时，
所以要从special考虑，1 <= special.length <= 10^5
*/

class Solution2274 {
public:
    int maxConsecutive(int bottom, int top, vector<int>& special) {
        int ans = 0;
        sort(special.begin(), special.end());
        ans = max(ans, special.front() - bottom);
        ans = max(ans, top - special.back());
        for (int i = 1; i < special.size(); i++) {
            ans = max(ans, special[i] - special[i - 1] - 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2274 solu;
    cout << solu.maxConsecutive(2, 9, *new vector<int>({4, 6})) << endl;
    return 0;
}
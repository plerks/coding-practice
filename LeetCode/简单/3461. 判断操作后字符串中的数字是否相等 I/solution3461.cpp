/*
url: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-i/
标签: LeetCode第438场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3461 {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        vector<int> d;
        for (char c : s) d.push_back(c - '0');
        while (d.size() > 2) {
            vector<int> nd;
            for (int i = 0;i < d.size() - 1; i++) {
                nd.push_back((d[i] + d[i + 1]) % 10);
            }
            d = nd;
        }
        return d[0] == d[1];
    }
};

int main(int argc, char const *argv[]) {
    Solution3461 solu;
    cout << solu.hasSameDigits("3902") << endl;
    return 0;
}
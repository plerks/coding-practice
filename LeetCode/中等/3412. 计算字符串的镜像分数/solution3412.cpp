/*
url: https://leetcode.cn/problems/find-mirror-score-of-a-string/description/
标签: LeetCode第431场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3412 {
public:
    long long calculateScore(string s) {
        vector<vector<int>> map(26);
        long long ans = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            char other = 25 - (c - 'a') + 'a';
            if (!map[other - 'a'].empty()) {
                ans += i - map[other - 'a'].back();
                map[other - 'a'].pop_back();
            }
            else map[c - 'a'].push_back(i); // i也要标记，这里要else
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3412 solu;
    cout << solu.calculateScore("aczzx") << endl;
    return 0;
}
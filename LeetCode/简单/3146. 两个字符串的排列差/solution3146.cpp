/*
url: https://leetcode.cn/problems/permutation-difference-between-two-strings/description/
标签: LeetCode第397场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3146 {
public:
    int findPermutationDifference(string s, string t) {
        vector<int> position(26, 0);
        for (int i = 0; i < s.length(); i++) {
            position[s[i] - 'a'] = i;
        }
        int ans = 0;
        for (int i = 0; i < t.length(); i++) {
            ans += abs(i - position[t[i] - 'a']);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

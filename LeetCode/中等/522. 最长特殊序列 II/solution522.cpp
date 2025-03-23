/*
url: https://leetcode.cn/problems/longest-uncommon-subsequence-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution522 {
public:
    // LeetCode392. 判断子序列
    bool isSubsequence(string s, string t) { // 判断s是否为t的子序列
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++; j++;
            }
            else j++;
        }
        return i == s.size();
    }

    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        int ans = -1;
        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (isSubsequence(strs[i], strs[j])) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans = max(ans, (int)strs[i].size());
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution522 solu;
    cout << solu.findLUSlength(*new vector<string>{"aba","cdc","eae"}) << endl;
    return 0;
}
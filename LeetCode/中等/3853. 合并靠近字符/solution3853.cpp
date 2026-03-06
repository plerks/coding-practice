/*
url: https://leetcode.cn/problems/merge-close-characters/
标签: LeetCode第177场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3853 {
public:
    string mergeCharacters(string s, int k) {
        int n = s.size();
        string ans;
        vector<int> lst(26, -1);
        for (int i = 0; i < n; i++) {
            char ch = s[i];
            // cout << ans << endl;
            if (lst[ch - 'a'] == -1) {
                lst[ch - 'a'] = ans.size(), ans.push_back(ch);
                continue;
            };
            if (ans.size() - lst[ch - 'a'] <= k) continue;
            else {
                lst[ch - 'a'] = ans.size();
                ans.push_back(ch);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
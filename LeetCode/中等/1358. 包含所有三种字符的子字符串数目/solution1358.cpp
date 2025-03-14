/*
url: https://leetcode.cn/problems/number-of-substrings-containing-all-three-characters/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1358 {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int cnt[3]{};
        int full = 0;
        int l = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            cnt[s[r] - 'a']++;
            if (cnt[s[r] - 'a'] == 1) full++;
            while (full >= 3) {
                cnt[s[l] - 'a']--;
                if (cnt[s[l] - 'a'] == 0) full--;
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1358 solu;
    cout << solu.numberOfSubstrings("abcabc") << endl;
    return 0;
}
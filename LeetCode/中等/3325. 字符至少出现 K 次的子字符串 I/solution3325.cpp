/*
url: https://leetcode.cn/problems/count-substrings-with-k-frequency-characters-i/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3325 {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();
        int freq[26]{};
        int cnt = 0; // 窗口出现次数>=k的字符数
        int l = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            freq[s[r] - 'a']++;
            if (freq[s[r] - 'a'] == k) cnt++;
            while (cnt >= 1) {
                freq[s[l] - 'a']--;
                if (freq[s[l] - 'a'] == k - 1) cnt--;
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3325 solu;
    cout << solu.numberOfSubstrings("abacb", 2) << endl;
    return 0;
}
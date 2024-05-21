/*
url: https://leetcode.cn/problems/minimum-substring-partition-of-equal-character-frequency/description/
LeetCode参考: https://leetcode.cn/problems/minimum-substring-partition-of-equal-character-frequency/solutions/2775377/hua-fen-xing-dpji-yi-hua-sou-suo-di-tui-s1nq0/
标签: LeetCode第130场双周赛, 判断所有数字相同
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3144 {
public:
    // 我的解法，通过
    int minimumSubstringsInPartition(string s) {
        int n = s.length();
        vector<int> dp(n, 0x3f3f3f3f); // dp[i]表示对子串s[0, i]的最少平衡子串数
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            vector<int> map(26, 0);
            for (int j = i; j >= 0; j--) {
                char ch = s[j];
                map[ch - 'a']++;
                int equalCount = 0;
                bool isLegal = true;
                for (int k = 0; k < 26; k++) {
                    if (map[k] == 0) continue;
                    if (equalCount == 0) {
                        equalCount = map[k];
                    }
                    else if (equalCount != map[k]) {
                        isLegal = false;
                        break;
                    }
                }
                if (isLegal) {
                    dp[i] = min(dp[i], j == 0 ? 1 : (dp[j - 1] + 1));
                }
            }
        }
        return dp[n - 1];
    }

    // 灵茶山艾府题解解法，在判断子串是否所有字母出现次数相同时，直接判断最高出现次数 * k是否为子串长度
    int minimumSubstringsInPartition_implementation2(string s) {
        int n = s.length();
        vector<int> dp(n, 0x3f3f3f3f); // dp[i]表示对子串s[0, i]的最少平衡子串数
        for (int i = 0; i < n; i++) {
            vector<int> map(26, 0);
            int k = 0; // 有多少个出现次数非0的字母
            int maxCount = 0; // 最高出现次数
            for (int j = i; j >= 0; j--) {
                char ch = s[j] - 'a';
                if (map[ch] == 0) k++;
                map[ch]++;
                maxCount = max(maxCount, map[ch]);
                if (i - j + 1 == k * maxCount) {
                    dp[i] = min(dp[i], j == 0 ? 1 : (dp[j - 1] + 1));
                }
            }
        }
        return dp[n - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution3144 solu;
    cout << solu.minimumSubstringsInPartition("fabccddg") << endl;
    cout << solu.minimumSubstringsInPartition_implementation2("fabccddg") << endl;
    return 0;
}

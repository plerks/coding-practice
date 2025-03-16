/*
url: https://leetcode.cn/problems/longest-repeating-character-replacement/
参考: https://leetcode.cn/problems/longest-repeating-character-replacement/solutions/586933/ti-huan-hou-de-zui-chang-zhong-fu-zi-fu-n6aza/
相关: LeetCode1156. 单字符重复子串的最大长度, [special]
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution424 {
public:
    // 我的做法，对每个r，找l使得非最大字母的个数<=k，时间复杂度O(nΣ)，这题Σ为26。
    int characterReplacement(string s, int k) {
        int n = s.size();
        int cnt[26]{};

        auto get_max = [&]() {
            int mx = cnt[0];
            for (int i = 1; i < 26; i++) mx = max(mx, cnt[i]);
            return mx;
        };

        int ans = 0;

        for (int l = 0, r = 0; r < n; r++) {
            cnt[s[r] - 'A']++;
            while ((r - l + 1) - get_max() > k) {
                cnt[s[l] - 'A']--;
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }

    // 官方题解做法，时间复杂度O(n)。这个滑窗很特殊，r每次固定往右走一步，但是l每次最多走一步(0步或1步)，不是常见的每次l一直往右走直到不满足条件
    int characterReplacement_implementation2(string s, int k) {
        /* 考虑窗口长度，当我们发现一个长为len的窗口合法后，所有更短的窗口都不需要考虑了，
        只需要考虑长度>len的窗口是否合法。若当前尝试的窗口长度为len，若当前窗口不合法，
        则l++, r++；若合法，则维持l不变，r++，尝试长为len + 1的窗口[l, r + 1]。
        可不可能[l, r + 1]前面有长为len + 1的合法窗口？例如，[l-1, r]是否要检查
        否，"是否合法"对于窗口长度是有单调性的，如果前面有长为len+1的合法窗口[x, y+1]，那么长为len的窗口[x, y]也必然合法，
        那么前面早就开始检查这个长为len + 1的窗口了。
        也就是说，当我们发现长为len的窗口合法后，立即不重不漏地开始尝试所有长为len + 1的窗口是否合法。
        
        如何知道历史最长合法窗口？获取历史最大频率。如何知道历史最大频率？
        右端点筛选，每次从右端点引入字符时检查nums[r]频率
        */
        int n = s.size();
        int cnt[26]{};
        int maxFreq = 0; // 历史最大频率
        int l = 0, r = 0;
        for (; r < n; r++) {
            cnt[s[r] - 'A']++;
            maxFreq = max(maxFreq, cnt[s[r] - 'A']);

            /* 检查合法性，可能当前窗口的最大频率根本不是maxFreq，但是也这样计算，
            既然前面r - l + 1 - maxFreq <= k没有发生，那么只要maxFreq没有发生变动，
            这个条件现在也必然不会满足，一定不会增长一步。若maxFreq发生了变动，那么这时
            maxFreq确实是当前窗口的准确值了，也确实应该检查是否合法（以使尝试窗口长度增加1）
            */
            /* 每当maxFreq变大时，通过这里发生r - l + 1 - maxFreq <= k，要把窗口增长1。
            若[l, r + 1]还合法（注意这时候maxFreq还是真实的窗口最大频率），则窗口还能继续增长。
            */
            if (r - l + 1 - maxFreq > k) { // 不合法，窗口向右平移一步
                cnt[s[l] - 'A']--;
                l++;
            }
        }
        return r - l; // 当前尝试的长度是r - l + 1，最后一次尝试成功的长度是r - l。也可以return min(maxFreq + k, n);
    }
};

int main(int argc, char const *argv[]) {
    Solution424 solu;
    cout << solu.characterReplacement("ABAB", 2) << endl;
    cout << solu.characterReplacement("AAAA", 2) << endl;

    cout << solu.characterReplacement_implementation2("ABAB", 2) << endl;
    cout << solu.characterReplacement_implementation2("AAAA", 2) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/longest-substring-of-all-vowels-in-order/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1839 {
public:
    // 我的写法
    int longestBeautifulSubstring(string word) {
        int n = word.size();
        vector<char> letter{'a', 'e', 'i', 'o', 'u'};
        int want = 0;
        int ans = 0;
        int len = 0;
        for (int i = 0; i < n;) {
            if (word[i] != letter[want]) {
                len = 0;
                want = 0;
                if (word[i] != 'a') i++; // i位置失配，若其为a，应当这个位置去开启下一轮，否则i++
                continue;
            }
            while (i < n && word[i] == letter[want]) {
                i++;
                len++;
            }
            if (want == 4) {
                ans = max(ans, len);
                want = 0;
                len = 0;
            }
            else {
                want++;
            }
        }
        return ans;
    }

    /* 参考官方题解评论区<https://leetcode.cn/problems/longest-substring-of-all-vowels-in-order/solutions/742722/suo-you-yuan-yin-an-shun-xu-pai-bu-de-zu-9wqg/comments/2275414/>，
    aeiou的大小是递增的！所以可以以下这样写： */
    int longestBeautifulSubstring_implementation2(string word) {
        int n = word.size();
        int ans = 0;
        for (int i = 0; i < n;) {
            if (word[i] != 'a') {
                i++;
                continue;
            }
            int start = i;
            int cnt = 1;
            i++;
            while (i < n && word[i] >= word[i - 1]) {
                if (word[i] > word[i - 1]) cnt++;
                i++;
            }
            if (cnt == 5) ans = max(ans, i - start);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1839 solu;
    // cout << solu.longestBeautifulSubstring("aeiaaioaaaaeiiiiouuuooaauuaeiu") << endl;
    cout << solu.longestBeautifulSubstring("aeaaeeiioouu") << endl;
    return 0;
}
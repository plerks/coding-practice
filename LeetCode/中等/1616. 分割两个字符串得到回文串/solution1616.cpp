/*
url: https://leetcode.cn/problems/split-two-strings-to-make-palindrome/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1616 {
public:
    bool isPalindrome(const string& s) {
        for (int i = 0; i <= (s.size() - 1) / 2; i++) {
            if (s[i] != s[s.size() - 1 - i]) return false;
        }
        return true;
    }

    // 我的解法
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size(); // a, b长度相同
        // a的前缀 + b的后缀
        int l = 0;
        while (l < n && a[l] == b[n - 1 - l]) l++;
        // 长度 > ⌊n/2⌋或者a/b之一的中间段是回文
        if (l >= n / 2 || isPalindrome(b.substr(l, n - 2 * l)) || isPalindrome(a.substr(l, n - 2 * l))) return true;

        // b的前缀 + a的后缀
        l = 0;
        while (l < n && b[l] == a[n - 1 - l]) l++;
        if (l >= n / 2 || isPalindrome(a.substr(l, n - 2 * l)) || isPalindrome(b.substr(l, n - 2 * l))) return true;
        
        return false;
    }

    /* 这篇题解看到的解法<https://leetcode.cn/problems/split-two-strings-to-make-palindrome/solutions/442635/split-two-strings-to-make-palindrome-by-ikaruga/>，
    从中心扩展，a,b中间有一段回文序列，要用二者中心回文更长的一方作为拼接成的回文串的中心(选更长是为了让剩余的左右部分能更轻松地完成回文匹配)，
    然后只需检查两端是否能完成回文匹配即可。这里两个功能只需定义一个函数，就是对给定的字符串x, y，从left位置开始，去找x往左，y往右能匹配多长，
    返回最远能匹配到的左边位置。
    */
    bool checkPalindromeFormation_implementation2(string a, string b) {
        int n = a.size();
        int left = min(findMatchLeft(a, a, n / 2 - 1), findMatchLeft(b, b, n / 2 - 1)); // 现在left是a, b二者中心匹配更长者的最长匹配左端点

        // 从中段的左右端点，往两端走，看能否匹配完。分a前缀 + b后缀 和 a后缀 + b前缀
        left = min(findMatchLeft(a, b, left), findMatchLeft(b, a, left));
        return left == -1; // left为-1说明能拼成回文
    }

    int findMatchLeft(string& x, string& y, int left) {
        while (left >=0 && x[left] == y[x.size() - 1 - left]) left--;
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution1616 solu;
    // cout << solu.checkPalindromeFormation("xbdef", "xecab") << endl;
    // cout << solu.checkPalindromeFormation("abdef", "fecab") << endl;
    // cout << solu.checkPalindromeFormation("abda", "acmc") << endl;
    cout << solu.checkPalindromeFormation("pvhmupgqeltozftlmfjjde", "yjgpzbezspnnpszebzmhvp") << endl;
    cout << solu.checkPalindromeFormation("aejbaalflrmkswrydwdkdwdyrwskmrlfqizjezd", "uvebspqckawkhbrtlqwblfwzfptanhiglaabjea") << endl;
    return 0;
}
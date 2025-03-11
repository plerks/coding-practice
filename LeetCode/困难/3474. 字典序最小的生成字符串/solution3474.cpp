/*
url: https://leetcode.cn/problems/lexicographically-smallest-generated-string/
参考: https://www.bilibili.com/video/BV1QP9bY3EL6/
      https://leetcode.cn/problems/lexicographically-smallest-generated-string/solutions/3592764/liang-chong-fang-fa-tan-xin-bao-li-pi-pe-gxyn/
标签: LeetCode第439场周赛, Z函数
*/

// 这次周赛1题

#include <bits/stdc++.h>

using namespace std;

class Solution3474 {
public:
    /* 参考灵茶题解，
    先根据T的位置，把ans所有能确定的位置的字符填上，此时ans可能会有一些位置是待定的，要字典序最小，这些?位置要尽量填a，
    然后再看F的位置，现在要求F，但是有可能现在ans这一节==str2，也就是说这个F是假F（F'），要使其成为真F，要把区间内最后
    一个待定的?从暂填的a改成b。然后，这题最关键的性质来了，例如，i位置该为F，现在ans[i, i + m)和str2相等了，通过范围内
    的? -> a -> b使i处的F成立之后，可以保证: [i, i + m)内的F一定都是真F，为什么？
    不好详细证，只好大概解释下：
    首先，若一个位置为T，则接下来的m个位置都得固定为str2的字符而不能为?（如果两个连续位置为T，则可推出来str2所有字符相同，这是最好想的情况），
    所以ans第一轮填完后会长成这样：△ △ △ △ △ ? ? ? ? △ △ △ △ △，（△表示已经固定了字符，？表示是待定，最好能填a）
    当找到第一个位置i为假F，我们找到了[i, i + m)范围内最后一个?，把其从a改成b之后，能说明：[i, i + m)内的F一定是真F，
    例如：（以下用t来称呼str2）
        0 1 2 3 4 5 6 7 9 10
        △ △ △ △ △ ? ? ? ? △ △ △ △ △
            - - - a a
    ans[0]为T，则ans[0, 4]都确认了字符，现在ans[2]的位置的F为假F，所以我们把找到的ans[6]从a改成b，
    ans[2]的位置的F为假F（说明这段t和ans完全匹配），说明t的后缀为aa，而ans[3,4]也是t的后缀，说明ans[3,4]也是aa，
    则t[1,2]也是aa(因为在上下同一位置)，然后接着用关系，则t[0] == t[2] == a，那么t全为a！那么在[3, 6]范围的F，一定为真F！
    也就是说，不会存在两段有相交的假F，当发现一个假F时，要么这段范围内有?，从而可以把? -> a -> b以使其为真F，
    要么这段范围没有?，构造不出来ans，直接返回""。
    然后，可以直接跳到i + m位置继续检查F，因为(i, i + m)的部分，因为ans[6]从a改成了b（关键点！），一定不会匹配。
    这样，只会存在把待定位置的a改成b，不会重复改同一个位置（不会需要把b改成c）。
    这种情况，后缀有一定长度的全a，从全a往斜上方刷，然后往下，再往斜上，能把整个t全刷成a，这样就很容易证明了
    还有种情况，t == baaab
        0 1 2 3 4 5 6 7 8 9 10
        b a a a b ? ? ? b a a a b
    然后ans[4]的位置是假F，这种跨了整个?区域就不能把整个t刷成全a了，但是，将ans[7]从a改成b后，也是只需要从9的位置开始找假F

    证明很不严谨，但是真要证明得很严格的话估计得很麻烦。
    */
    string generateString(string str1, string str2) {
        // 直接暴力O(nm)，题目范围小能过
        string &s = str1, &t = str2;
        int n = s.size(), m = t.size();
        string ans(n + m - 1, '?');
        for (int i = 0; i < n; i++) { // 先填T
            if (s[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != '?' && ans[i + j] != t[j]) return ""; // T之间就有冲突
                    ans[i + j] = t[j];
                }
            }
        }
        string old_ans = ans;
        for (char &c : ans) {
            if (c == '?') c = 'a';
        }
        // 看F
        for (int i = 0; i < n; i++) {
            if (s[i] == 'T') continue;
            bool ok = true; // 能否把假F改成真F
            if (t == ans.substr(i, m)) {
                ok = false;
                for (int j = i + m - 1; j >= i; j--) {
                    if (old_ans[j] == '?') {
                        ans[j] = 'b'; // 不需要是ans[j]++;
                        ok = true;
                        break;
                    }
                }
            }
            if (!ok) return "";
        }
        return ans;
    }

    vector<int> z_function(const string& s) {
        int n = s.size();
        vector<int> z(n, 0);
        // z[0] = 0;
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r) {
                z[i] = min(z[i - l], r - i + 1);
            }
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    /* 灵茶题解解法二，用Z函数优化
    时间复杂度O(n + m)
    */
    string generateString_implementation2(string str1, string str2) {
        string &s = str1, &t = str2;
        int n = s.size(), m = t.size();
        string ans(n + m - 1, '?');

        vector<int> z = z_function(t);
        int pre = 0; // 之前已经填到了pre位置(pre这个点没填)，两个相邻的T，第一个T填了之后可能已经帮第二个T填了一部分
        // 处理T，顺便用z函数检查T之间的合法性
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') continue;
            int size = max(0, pre - i); // 前面的T可能已经帮当前的T填了[i, pre)
            // 但是帮填的部分要合法，t的长为size的前后缀必须相等
            if (size > 0 && z[m - size] < size) return "";
            // 当前的T继续填自己
            for (int j = size; j < m; j++) {
                ans[i + j] = t[j];
            }
            pre = i + m;
        }

        /* 为了处理F，需要知道当前F是否完全匹配了，需要t + ans的z函数，完全匹配的话，要改
        <= i + m的最靠右的?（a->b），假F的区间互不相交，所以ans变化了不影响。
        */
        // 先计算<=i + m的最靠右的？
        vector<int> cand(n + m - 1);
        for (int i = 0, last = -1; i < n + m - 1; i++) {
            if (ans[i] == '?') {
                last = i;
                ans[i] = 'a'; // 顺便把?改成a
            }
            cand[i] = last;
        }

        z = z_function(t + ans);

        // 处理F
        for (int i = 0; i < n; i++) {
            if (s[i] == 'T') continue;
            if (z[i + m] >= m) { // 假F，由于把t接到了ans前，可能匹配长度>m
                int j = cand[i + m - 1]; // <= i + m - 1的最后一个?
                if (j < i) {
                    return ""; // 没有合适位置的?
                }
                else ans[j] = 'b';
                i = j; // i直接跳到j，接着i++，从这次改动的?的下一个位置开始找假F
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3474 solu;
    cout << solu.generateString_implementation2("TFTF", "ab") << endl;
    cout << solu.generateString_implementation2("TTFFT", "fff") << endl;
    cout << solu.generateString_implementation2("FFTFFF", "a") << endl;
    return 0;
}
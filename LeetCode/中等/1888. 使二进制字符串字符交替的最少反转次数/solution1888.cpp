/*
url: https://leetcode.cn/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/description/
参考: https://leetcode.cn/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/solutions/815407/shi-er-jin-zhi-zi-fu-chuan-zi-fu-jiao-ti-i52p/
相关: LeetCode438. 找到字符串中所有字母异位词
标签: 【题单】滑动窗口与双指针, 前后缀分解
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1888 {
public:
    // 我的解法
    int minFlips(string s) {
        int n = s.size();
        /* 条件1表示可以以任何一个位置为起点，最终都是1010...或者0101交替，
        关键点在于奇偶位置上0和1的个数
        */
        int even0 = 0; // 偶数位置上0的个数
        int even1 = 0;
        int odd0 = 0;
        int odd1 = 0;
        for (int i = 0; i < n - 1; i++) {
            if (i % 2 == 0) {
                if (s[i] == '0') even0++;
                else even1++;
            }
            else {
                if (s[i] == '0') odd0++;
                else odd1++;
            }
        }
        int ans = INT_MAX;
        int r = n - 1;
        // 枚举左端点
        for (int l = 0; l < n; l++) {
            if ((n - 1) % 2 == 0) {
                if (s[r] == '0') even0++;
                else even1++;
            }
            else {
                if (s[r] == '0') odd0++;
                else odd1++;
            }
            r = (r + 1) % n;
            // 如果l位置要变成0，那就是even0 + odd1，否则就是even1 + odd0
            ans = min({ans, even0 + odd1, even1 + odd0});
            if (s[l] == '0') even0--;
            else even1--;
            swap(even0, odd0);
            swap(even1, odd1);
        }
        return ans;
    }

    /* 参考官方题解的思路，前后缀分解，
    若n为偶数，最终变为1010...10或者0101...01，若n为奇数，最终变为1010...101或者0101...010
    s一定有一个位置是不需要变的，枚举这个位置，然后就可以前后缀分解。
    */
    int minFlips_implementation2(string s) {
        int n = s.size();
        vector<array<int, 2>> pre(n); // pre[i][j]表示把s[0...i]变成以j为末尾的交替串所需的操作次数
        // pre[i][j] = pre[i - 1][(j + 1) % 2] + j ^ (s[i])，(j + 1) % 2是为了把0变成1，把1变成0
        pre[0][0] = 0 ^ (s[0] - '0');
        pre[0][1] = 1 ^ (s[0] - '0');
        for (int i = 1; i < n; i++) {
            pre[i][0] = pre[i - 1][1] + (0 ^ (s[i] - '0'));
            pre[i][1] = pre[i - 1][0] + (1 ^ (s[i] - '0'));
        }
        if (n % 2 == 0) return min(pre[n - 1][0], pre[n - 1][1]);
        // 如果n为奇数，结果串中会出现00或者11，枚举这个位置
        vector<array<int, 2>> suf(n + 1);
        suf[n - 1][0] = 0 ^ (s[n - 1] - '0');
        suf[n - 1][1] = 1 ^ (s[n - 1] - '0');
        for (int i = n - 1; i >= 0; i--) {
            suf[i][0] = suf[i + 1][1] + (0 ^ (s[i] - '0'));
            suf[i][1] = suf[i + 1][0] + (1 ^ (s[i] - '0'));
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min({ans, pre[i][0] + suf[i + 1][0], pre[i][1] + suf[i + 1][1]});
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1888 solu;
    // cout << solu.minFlips("111000") << endl;
    cout << solu.minFlips("01001001101") << endl;

    cout << solu.minFlips_implementation2("01001001101") << endl;
    return 0;
}
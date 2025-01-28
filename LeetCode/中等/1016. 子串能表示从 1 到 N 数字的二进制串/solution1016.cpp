/*
url: https://leetcode.cn/problems/binary-string-with-substrings-representing-1-to-n/description/
参考: https://leetcode.cn/problems/binary-string-with-substrings-representing-1-to-n/solutions/2265097/san-chong-suan-fa-cong-bao-li-dao-you-hu-nmtq/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1016 {
public:
    /* 灵茶题解解法一，直接枚举[1, n]是否在s中，虽然此题1 <= n <= 10^9，但是1 <= s.length <= 1000，
    所以无论如何s都只能容纳下一小部分x，枚举会很快退出。
    具体来说，对于[2^(k-1), 2^k - 1]内的所有二进制数，s要多长才能包含这些数？
    [2^(k-1), 2^k - 1]之中的数是100...00 - 111...11的形式，长度相同(k)，最大程度地考虑复用，那么每多表示一个数，
    s就要增长1
        注意这里不可能出现 xxxxxx
                         yyyyyy
                          zzzzzz
        中间还能免费隐含一个 wwwwww 的可能，都是长度相同的数，每多加一个都要至少有一个开头。
    那么，要表示完[2^(k-1), 2^k - 1]的数，s的长度(记为m)至少要 k + 2^k - 2^(k - 1)，同时，表示完所有长度为m的数，更短的数也一定被
    表示完了，(表示完了[100, 111]，则顺便[00, 11]就表示完了)。
    所以，以s最高1000的length，[1, 1e9]的数只能表示很小一部分，就算全部集中在枚举的开头，也持续不了多久，很快就会找到未出现的情况。

    s要包含[2^(k-1), 2^k - 1]和[2^k, n]的所有数，所以
    m < k + 2^k - 1 或者 m < k + 1 + n - 2^k 时，直接返回false
    */
    bool queryString(string s, int n) {
        for (int x = 1; x <= n; x++) {
            auto bin_str = bitset<32>(x).to_string();
            bin_str = bin_str.substr(bin_str.find('1'));
            if (s.find(bin_str) == string::npos) {
                return false;
            }
        }
        return true;
    }

    /* 灵茶题解解法二，把所有s的子串都放到哈希表中，看是否有n个，子串枚举时要动态维护，而非O(n^2)的枚举
    */
    bool queryString_implementation2(string s, int n) {
        int m = s.size();
        unordered_set<int> st;
        for (int i = 0; i < m; i++) {
            int x = s[i] - '0'; // 前导0不要
            if (x == 0) continue;
            for (int j = i + 1; j <= m && x <= n; j++) {
                st.insert(x);
                x = (x << 1) | (s[j] - '0');
            }
        }
        return st.size() == n;
    }

    /* 灵茶题解解法三，假设n的形式是1xxx..xx，只需考虑s中是否表示完了[1000..00, 1xxx...xx]和
    [10..00, 11..11]，
    此外，[1000..00, 1xxx...xx]向右右移一位能得到[10..00, 11..11]中的部分数，所以第二种情况枚举还要少些。
    具体来说，设k为n的二进制长度-1，即2^k为第一个<=n的2的幂次。
    s需要表示完[2^k, n]和[2^(k-1), 2^k - 1]的所有数，而[2^k, n]右移一位可以得到[2^k, n / 2]的所有数，因此第
    二种情况只需枚举[n / 2 + 1, 2^k - 1]。

    最终为长度分别为k和k + 1的两次定长滑窗，时间复杂度为O(m)，m为s的长度
    */
    bool queryString_implementation3(string s, int n) {
        int m = s.size();
        int k = 32 - __builtin_clz(n) - 1;
        // m < k + 2^k - 1 或者 m < k + 1 + n - 2^k 时，直接返回false
        if (m < k + (1 << k) - 1 || m < k + 1 + n - (1 << k)) return false;

        // 滑窗长度固定为k，对s滑窗，检查[lower, upper]范围内的数是否都在s中出现
        auto check = [&](int k, int lower, int upper) {
            if (lower > upper) return true;
            unordered_set<int> seen;
            int mask = (1 << (k - 1)) - 1;
            int x = 0;
            if (k - 1 == 0) x = 0; // 窗口初始化长度为k - 1，如果k - 1为0，s.substr(0, k - 1)会是空串，stoi会抛出异常
            // stoi三个参数(字符串, 起始位置, 进制)
            else x = stoi(s.substr(0, k - 1), nullptr, 2);
            for (int i = k - 1; i < m; i++) {
                // & mask 是滑窗从左边出，| (s[i] - '0') 是滑窗从右边入
                x = ((x & mask) << 1) | (s[i] - '0');
                if (lower <= x && x <= upper) seen.insert(x);
            }
            return seen.size() == upper - lower + 1;
        };

        return check(k + 1, 1 << k, n) && check(k, n / 2 + 1, (1 << k) - 1);
    }
};

int main(int argc, char const *argv[]) {
    Solution1016 solu;
    cout << solu.queryString("0110", 3) << endl;
    cout << solu.queryString_implementation2("0110", 3) << endl;
    cout << solu.queryString_implementation3("0110", 3) << endl;
    cout << solu.queryString_implementation3("1", 1) << endl;
    return 0;
}
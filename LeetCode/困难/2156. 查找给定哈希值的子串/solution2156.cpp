/*
url: https://leetcode.cn/problems/find-substring-with-given-hash-value/description/
参考: https://oi-wiki.org/string/hash/
      https://www.bilibili.com/video/BV1Ha411E7re/
      https://leetcode.cn/problems/find-substring-with-given-hash-value/solutions/1239542/dao-xu-hua-dong-chuang-kou-o1-kong-jian-xpgkp/
标签: 【题单】滑动窗口与双指针, 字符串哈希
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2156 {
public:
    string subStrHash(string s, int p, int mod, int k, int hashValue) {
        /* 字符串哈希一般对abc哈希为ap^2 + bp + c，这题的定义是对abc映射为a + bp + cp^2。
        为了用前一种定义，把s反转或者反向滑窗。
        ap^2 + bp + c变为bp^2 + cp + d时，只需(bp + c) * p + d。
        如果用a + bp + cp^2的定义，变成b + cp + dp^2时要除p而不是乘，应该要用求组合数中逆元的概念
        */
        reverse(s.begin(), s.end());
        int n = s.size();
        long long hash = 0;
        long long pk = 1; // p的k次方
        for (int i = 0; i < k; i++) {
            // 秦九韶算法
            hash = (hash * p + (s[i] & 31)) % mod; // 用&31取出字母的编号，得益于字母ascii码的二进制特点
            pk = pk * p % mod; // %的优先级比*/低，比+-高
        }
        // 把s反转了，题目要求第一个出现的位置，那么现在就要变成最后一个出现的位置，求的是max
        int ans = -1;
        if (hash == hashValue) ans = k - 1; // 记录最大的右端点
        for (int i = k; i < n; i++) {
            // 注意长度为k，最高次项的幂次是k - 1。+mod防负数
            hash = ((hash * p) + (s[i] & 31) - (s[i - k] & 31) * pk % mod + mod) % mod;
            if (hash == hashValue) ans = i;
        }
        // 题目保证hash值等于hashValue的子串一定存在
        string ans_string = s.substr(ans - k + 1, k);
        reverse(ans_string.begin(), ans_string.end());
        return ans_string;
    }
};

int main(int argc, char const *argv[]) {
    Solution2156 solu;
    cout << solu.subStrHash("leetcode", 7, 20, 2, 0) << endl;
    return 0;
}
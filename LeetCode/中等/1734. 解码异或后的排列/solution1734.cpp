/*
url: https://leetcode.cn/problems/decode-xored-permutation/
参考: https://leetcode.cn/problems/decode-xored-permutation/solutions/769516/gong-shui-san-xie-note-bie-pian-li-yong-zeh6o/
相关: LeetCode2683. 相邻值的按位异或, LeetCode1720. 解码异或后的数组
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1734 {
public:
    /* 此题与LeetCode2683相比，无法枚举值以破除循环依赖的关系，找不到算perm的起点，
    能推得的一个结论是encoded的所有元素异或，得到的值为perm[0] ^ perm[n - 1]，还是没用。

    题目条件 perm为[1, n]的排列，且n为奇数。

    参考宫水三叶题解，隔一个数来看，例如 perm 为 a b c d e，则encoded为：
    a b
    b c
    c d
    d e
    隔一个数来看就是 a ^ b ^ c ^ d，而 a ^ b ^ c ^ d ^ e = xor[1, n]，从而可求得e。然后就是LeetCode1720了
    */
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1;
        int a = 0;
        for (int i = 0; i < encoded.size(); i += 2) a ^= encoded[i];
        int total = 0;
        for (int i = 1; i <= n; i++) total ^= i;
        int last = total ^ a;
        vector<int> ans(n);
        ans[n - 1] = last;
        for (int i = n - 2; i >= 0; i--) {
            ans[i] = ans[i + 1] ^ encoded[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1734 solu;
    auto a = solu.decode(*new vector<int>{6,5,4,6});
    return 0;
}
/*
url: https://leetcode.cn/problems/find-xor-sum-of-all-pairs-bitwise-and/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1835 {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int ans = 0;
        for (int i = 0; i < 31; i++) {
            int a = 0, b = 0; // arr1和arr2这一位上1的个数
            for (int x : arr1) if ((x >> i) & 1) a++;
            for (int x : arr2) if ((x >> i) & 1) b++;
            if ((a & 1) && (b & 1)) ans |= 1 << i; // 一共有 a * b 种方式 AND 出来 1，然后异或结果取决于 a * b 的奇偶性
        }
        return ans;
    }

    // 参考灵茶题解，用 AND 对 XOR 的分配律：a & (b ^ c) = (a & b) ^ (a & c)。
    // 例如 arr1 = [a, b], arr2 = [c, d, e]
    // 则考虑 (a & c) ^ (a & d) ^ (a & e)
    // 变成 (a & (c ^ d)) ^ (a & e) = a & (c ^ d ^ e)
    // 所以，答案为， xor(arr1) & xor(arr2)
    int getXORSum_implementation2(vector<int>& arr1, vector<int>& arr2) {
        return accumulate(arr1.begin(), arr1.end(), 0, bit_xor()) & accumulate(arr2.begin(), arr2.end(), 0, bit_xor());
    }
};

int main(int argc, char const *argv[]) {
    Solution1835 solu;
    cout << solu.getXORSum(*new vector<int>{1,2,3}, *new vector<int>{6,5}) << endl;
    cout << solu.getXORSum(*new vector<int>{12}, *new vector<int>{4}) << endl;
    return 0;
}
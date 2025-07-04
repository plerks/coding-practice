/*
url: https://leetcode.cn/problems/sum-of-all-subset-xor-totals/
参考: https://leetcode.cn/problems/sum-of-all-subset-xor-totals/solutions/3614974/on-shu-xue-zuo-fa-pythonjavaccgojsrust-b-9txy/
标签: 【算法题单】位运算, 数学
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1863 {
public:
    // 我的解法
    int subsetXORSum(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int cnt0 = 0, cnt1 = 0;
            for (int x : nums) {
                if ((x >> i) & 1) cnt1++;
                else cnt0++;
            }
            // 0任选，1里选奇数个出来
            long long t = 0;
            for (int i = 1; i <= cnt1; i += 2) t += comb(cnt1, i);
            ans += (1LL << i) * (1LL << cnt0) * t;
        }
        return ans;
    }

    long long comb(int n, int m) {
        return factorial(n) / factorial(m) / factorial(n - m);
    }

    long long factorial(int n) {
        long long res = 1;
        for (int i = 1; i <= n; i++) res *= i;
        return res;
    }

    /* 灵茶题解做法，有更简洁的结论。
    还是按位来算，若nums这一位全为0，则为0。
    若nums这一位有1，则能贡献多少个异或值为1的集合？
    考虑其中1个1 和 剩下元素的幂集元素，这些幂集元素的异或值要么是1，要么是0，
    为1的部分这个1不选，为0的部分这个1选，于是为1的总方案数为 2^(n-1)。

    如何知道nums哪些位存在1？或一遍
    */
    int subsetXORSum_implementation2(vector<int>& nums) {
        int n = nums.size();
        int or_ = 0;
        for (int x : nums) or_ |= x;
        return or_ << (n - 1);
    }

    /* 灵茶题解中证明了 ΣC(n, 2i+1) 之和为多少
    (1 + 1)^n = C(n,0) + C(n,1) + ... + C(n,n)
    (1 - 1)^n = C(n,0) - C(n,1) + ... + (-1)^n * C(n,n)
    相减即可得到从n个元素里选奇数个出来，方案数为 2^(n-1)

    这也可以通过subsetXORSum_implementation2()的方式证明，
    考虑其中一个元素选或不选的情况，剩下元素的选取方案总共2^(n-1)种，分元素个数为 奇 ∪ 偶
    总选取个数为奇数的情况一共 选 ∪ { 偶 } + 不选 ∪ { 奇 }，一共 2^(n-1)种。

    也就是说从n (n >= 1)个球里选，总数为奇数的方案和总数为偶数的方案数是一样的。

    若 n 为 0，则要特判返回 0
    */
    int subsetXORSum_implementation3(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int cnt0 = 0, cnt1 = 0;
            for (int x : nums) {
                if ((x >> i) & 1) cnt1++;
                else cnt0++;
            }
            // 0任选，1里选奇数个出来
            ans += (1LL << i) * (1LL << cnt0) * (cnt1 ? 1LL << (cnt1 - 1) : 0);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1863 solu;
    cout << solu.subsetXORSum(*new vector<int>{1, 3}) << endl;
    cout << solu.subsetXORSum_implementation2(*new vector<int>{1, 3}) << endl;
    cout << solu.subsetXORSum_implementation3(*new vector<int>{1, 3}) << endl;
    return 0;
}
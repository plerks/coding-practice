/*
url: https://leetcode.cn/problems/maximum-xor-product/
相关: LeetCode2897. 对数组执行操作使平方和最大
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2939 {
public:
    /* 考虑a和b [0, n - 1]的某一位
    若是0 0，则可变成1 1
    若是1 1，则可维持1 1
    若是1 0 / 0 1，把小的变成1，大的变成0，因为这个2^i相当于让别的左移，让大的左移结果更大。
    仅仅看开始时刻的大小还不行，[4,7,3]这个用例，这样会把4变7，7变3，又变回去了。所以，每次都要新判断大小。
    */
    int maximumXorProduct(long long a, long long b, int n) {
        constexpr int MOD = 1e9 + 7;
        for (int i = n - 1; i >= 0; i--) { // 必须从高位到底位遍历，这样每次才能判断出来大小
            if (a > b) swap(a, b);
            int aa = (a >> i) & 1;
            int bb = (b >> i) & 1;
            if (aa == 0 && bb == 0) {
                a |= 1LL << i;
                b |= 1LL << i;
            }
            else if (aa == 1 && bb == 1) continue;
            else { // 01 10的情况
                if (aa == 0) {
                    a |= 1LL << i;
                    b &= ~(1LL << i);
                }
            }
        }
        return (a % MOD) * (b % MOD) % MOD;
    }

    /* 参考灵茶题解，我的做法是对的，首先，00和11的情况很明确。
    对于01和10的情况，无论x这一位是什么，1的个数是不变的，也就是说 (a^x) + (b^x) 是定值，要让 (a^x) * (b^x)尽量大，
    根据均值不等式，就要让二者尽量相等，于是，遇到01/10时，尽量将1分配给小的。这是更好的解释。
    */
};

int main(int argc, char const *argv[]) {
    Solution2939 solu;
    cout << solu.maximumXorProduct(12, 5, 4) << endl;
    return 0;
}
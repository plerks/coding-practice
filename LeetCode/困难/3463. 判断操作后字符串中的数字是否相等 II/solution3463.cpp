/*
url: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/
参考: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/3086169/mo-shu-wei-he-shu-shi-de-zu-he-shu-by-en-8x7t/
      https://oi-wiki.org/math/number-theory/lucas/
      https://oi-wiki.org/math/number-theory/crt/
标签: LeetCode第438场周赛, 组合数学, 欧拉定理, 扩展Lucas定理, 中国剩余定理, 组合数模非素数
*/

#include <bits/stdc++.h>

using namespace std;

// 用欧拉定理求模10意义下的组合数，注意：这里的代码只能用于模数为10的情况
const int MX = 1e5 + 1; // MX = 具体题目需要涉及到的最大范围 + 1，阶乘最多算到(MX - 1)!
const int MOD = 10; // 模数为10

int f[MX]; // n!去除2和5的幂次后 % MOD
int inv_f[MX]; // 逆元
int p2[MX]; // p2[x]表示x中2的幂次
int p5[MX];

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

/* 先从左到右计算x! mod m，然后在n!的位置，已知n! mod m的值，由欧拉定理可知n!在mod m意义下的逆元(n!)^(-1)为(n! mod m)^3，
然后(n-1)^(-1) = (n!)^(-1) * n，于是从右往左算x!的逆元
*/
auto init = []() {
    f[0] = 1;
    // 从左往右
    for (int i = 1; i < MX; i++) {
        int x = i;
        // 计算2的幂次
        int e2 = __builtin_ctz(x);
        x >>= e2;
        // 计算5的幂次
        int e5 = 0;
        while (x % 5 == 0) {
            e5++;
            x /= 5;
        }
        f[i] = f[i - 1] * x % MOD;
        p2[i] = p2[i - 1] + e2;
        p5[i] = p5[i - 1] + e5;
    }

    // 从右往左
    inv_f[MX - 1] = fastPow(f[MX - 1], 3); // 欧拉定理找n!的逆元
    for (int i = MX - 1; i > 0; i--) {
        int x = i;
        x >>= __builtin_ctz(x);
        while (x % 5 == 0) {
            x /= 5;
        }
        inv_f[i - 1] = inv_f[i] * x % MOD;
    }
    return 0;
}();

const int POW2[4] = {2, 4, 8, 6}; // 2的幂次mod 10是1, 2, 4, 8, 6, 2, 4, 8, 6 ...
// 而5的幂次只要幂次>0，mod 10都是5

int comb(int n, int m) {
    // 上面的f和inv_f是剔除了2和5的幂次的，这里要乘回来
    // p2[n] - p2[k] - p2[n - k]代表n!/m!(n-m)!中2的幂次，一定>=0，见勒让德定理

    // return f[n] * inv_f[m] * inv_f[n - m] *
    //         fastPow(2, p2[n] - p2[m] - p2[n - m]) *
    //         fastPow(5, p5[n] - p5[m] - p5[n - m]) % MOD; // 这里每个乘积因子都<10，较小不会溢出，不用中途取模
    
    int e2 = p2[n] - p2[m] - p2[n - m];
    return f[n] * inv_f[m] * inv_f[n - m] *
            (e2 > 0 ? POW2[(e2 - 1) % 4] : 1) *
            (p5[n] - p5[m] - p5[n - m] > 0 ? 5 : 1) % MOD;
}

/* 受这里POW2发生循环的启发(2的幂次mod 10是1, 2, 4, 8, 6, 2, 4, 8, 6 ...)，想到这样一个问题：
a^x mod m，x = 0, 1, 2, ... ，是否一定会随x增大发生循环呢？
我感觉好像是的，但是不确定证明对不对，我的证明如下：
如果gcd(a, m) = 1，则由欧拉定理a^φ(m) ≡ 1 (mod m)，则φ(m)就是周期，a^0就开启了循环节(也就是说a^0, ... a^(φ(m) - 1); a^φ(m), ... a^(φ(m) - 1 + m); ...)这样循环

如果gcd(a, m)不为1，则如果a >= m，将a用m进制来表示，a^x mod m = (d_i * m^i + ... + d_0)^x mod m = d0^x mod m，
于是问题取决于d0^x mod m是否会循环。于是只需：

下证a < m时，a^x mod m一定会循环。
当gcd(a, m) = 1时，上面已经分析了，
当gcd(a, m) 不为1时，设a的素因子分解为 p1^e1 * p2^e2 * ... * pn^en，
现在证明 p^x mod m 一定会循环：
    若gcd(p, m) = 1，显然。
    若gcd(p, m)不为1，则gcd(p, m) = p，考虑p^x = km + r，则当x > 1时，p^(x-1) = k(m/p) + r/p，
    p | m则，r/p = p^(x-1) - k(m/p)为整数，而r/p是 p^(x-1) mod m/p 的余数，p与m/p二者互质，是会循环的，
    所以r也会发生循环。
由于 p^x mod m 会循环，则p^(ex) = p^x * p^x * ... * p^x mod m会循环。
由于每个 p^(ex) mod m 会循环，则 a^x mod m 会循环(取a每个因子的周期相乘即为周期)。

综上，a^x mod m，x = 0, 1, 2, ... ，一定会发生循环，无论a, m取任意正整数。

上面的过程想复杂了，用鸽笼原理就行，a^x mod m，余数的取值有限，一旦某一次xj与之前一次xi余数相同，则接着就会循环。
这样也能解释为什么前面可能出现一段不进入循环的，因为第一次发生重复时的 i > 0
*/

class Solution3463 {
public:
    /* 是杨辉三角跟着用例试一下就能发现，最终得到2个数字，第一个数是
    (C(n-2,0)*s[0] + C(n-2,1)*s[1] ... + C(n-2,n-2)*s[n-2]) % 10，
    于是需要求组合数，但是！这里这题要mod的是10，不是素数，不能用费马小定理那个求组合数模板，然后就不知道怎么做了。
    */
    /* 灵茶题解解法一，用欧拉定理：若gcd(a,m) = 1，则a^φ(m) ≡ 1 (mod m)，其中φ(m)是欧拉函数，表示的是小于等于m的数中和n互质的数的个数。
    注意欧拉函数的互质要考虑1，例如φ(10) = 4是因为有1, 3, 7, 9。此外φ(1) = 1，因为0与1互质(gcd(0, 1) = 1)，不过0与其他>1的数不互质(gcd(0, x) = x)。
    这里m为10，则φ(10) = 4，所以若gcd(a,10) = 1，则a^4 ≡ 1 (mod 10)，于是a^3 ≡ a^(-1) (mod 10)，于是逆元为a^3，
    借此可以把除法转换成乘法求组合数。
    但是欧拉定理要求gcd(a,10) = 1，这里求组合数涉及到的n!不一定能满足这个性质，所以要把n!和m的公共素因子提取出来，
    把2和5的幂次除出来，然后gcd(a', 10)就一定为1，
    因为把a把10的因子2和5都拿掉了，这样就能用欧拉定理了。

    不算预处理的时间，时间复杂度O(n)
    */
    bool hasSameDigits(string s) {
        // 最后的两个数字x1和x2的diff为(C(n-2,0)*s[0] + C(n-2,1)*s[1] ... + C(n-2,n-2)*s[n-2]) - (C(n-2,0)*s[1] + C(n-2,1)*s[2] ... + C(n-2,n-2)*s[n-1])
        int n = s.size();
        int diff = 0;
        for (int i = 0; i <= n - 2; i++) {
            diff += comb(n - 2, i) * (s[i + 1] - s[i]);
        }
        return diff % 10 == 0; // 这里diff可能为负，不过不影响
    }
};

int main(int argc, char const *argv[]) {
    Solution3463 solu;
    cout << solu.hasSameDigits("3902") << endl;
    cout << solu.hasSameDigits("34789") << endl;
    return 0;
}
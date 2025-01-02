/*
描述: 计算组合数的模板
参考: https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805408/zu-he-shu-xue-o1-gong-shi-pythonjavacgo-0fbgt/
      https://leetcode.cn/circle/discuss/mDfnkW/
相关: LeetCode3179. K 秒后第 N 个元素的值
标签: 组合数学, 组合数, 费马小定理
*/

#include <bits/stdc++.h>

using namespace std;

// 这是LeetCode3179[灵茶山艾府题解](https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/solutions/2805408/zu-he-shu-xue-o1-gong-shi-pythonjavacgo-0fbgt/)中的求组合数模板
const int MX = 2001; // 具体题目需要涉及到的最大范围
const int MOD = (int)(1e9 + 7); // 具体题目要mod的素数

long long fac[MX];
long long inv_fac[MX]; // 逆元

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

auto init = []() {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    /* 由费马小定理，a为整数，p为质数，则有a^p ≡ a (mod p)，若a不是p的倍数，则gcd(a, p) = 1(p为质数)，则由同余除法的性质，有a^(p - 1) ≡ 1 (mod p)。
    即a^(p - 2)是a在模p意义下的逆元，两边同乘b / a，有 b * a^(p - 2) ≡ b / a (mod p)，也就是说，模p意义下，求b / a可以转化为求b * a^(p - 2)。
    为什么非要将除法转换成乘法？
    由于题目的数字可能较大会发生溢出，所以一般会要求计算结果对某个素数取模，于是整个计算过程中，每一次运算就都进行取模，这样就不会因溢出而导致错误，
    而(a + b) mod m=((a mod m) + (b mod m)) mod m，(a * b) mod m=((a mod m) * (b mod m)) mod m
    对+和*，每步取模不仅能防止溢出产生错误，结果也是准确的，而对除法没有这样的性质，
    例如 24 / 8 mod 5 与 24 mod 5 / 8 mod 5 不相等。
    所以需要将除法转换成乘法。
    只要计算的过程中只涉及加减乘除运算，在将除法转换成乘法的前提下，只要不要一次运算就溢出(所以需要开long long，int加减乘不会溢出long long)，
    那么只要每步运算都mod p(尽早地在模p同余意义下把数变小防溢出)，由于模的性质(加减乘可提前取模，减可能出负数，减完后加上p即可)，
    结果就是完全正确的，就好像在用无限位长的BigInteger计算一样(但避免了使用BigInteger速度慢的问题)。
    */
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        // (1 * 2 * ... * i-1)的逆元(1 * 2 * ... * i-1)^-1 = (i - 1)^-1 * (i - 2)^-1 ... 1^-1，于是(1 * 2 * ... * i-1)的逆元可由(1 * 2 * ... * i)的逆元算出
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    // 模p意义下，通过逆元，把除法变成了乘法
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

long long arrange(int n, int m) {
    return fac[n] * inv_fac[n - m] % MOD;
}

int main(int argc, char const *argv[]) {
    cout << comb(5, 3) << endl;
    cout << arrange(6, 3) << endl;
    return 0;
}


/*
上面涉及到了一些同余的运算性质：
1. 若a≡b(mod p)，c≡d(mod p)，则ac≡bd(mod p)

2. 若ac≡bc(mod p)，c不等于0，则a≡b(mod p/gcd(c, p))，特殊地，若gcd(c, p) = 1则a≡b(mod p)
证明：ac≡bc(mod p)，则ac = k1 * p + r，bc = k2 * p + r，
     记g = gcd(c, p)，则记 c = mg，p = ng，
     则 amg = k1ng + r，bmg = k2ng + r，于是有 amg - bmg = (k1 - k2)ng，
     即 a - b = (k1 - k2) * (n / m) = (k1 - k2) * (p / g)，
     即 a≡b(mod p/g)

注意上面当a不是p的倍数时有 a^(p - 1) ≡ 1 (mod p)，
而当a是p的倍数时，则 a^(p - 1) ≡ 0 (mod p) (a = kp，则a^(p-1) = k^(p-1) * p^(p-1) ≡ 0 (mod p))
*/
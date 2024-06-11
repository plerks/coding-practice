/*
描述: 计算排列数的模板，从求组合数的模板修改而来
*/

#include <bits/stdc++.h>

using namespace std;

const int MX = 2001; // 具体题目需要涉及到的最大范围
const int MOD = (int)(1e9 + 7); // 具体题目要mod的素数

long long fac[MX];
long long inv_fac[MX];

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
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long arrange(int n, int m) {
    return fac[n] * inv_fac[n - m] % MOD;
}

int main(int argc, char const *argv[]) {
    cout << arrange(5, 3) << endl;
    return 0;
}

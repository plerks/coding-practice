/*
url: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/
参考: https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/3086169/mo-shu-wei-he-shu-shi-de-zu-he-shu-by-en-8x7t/
      https://oi-wiki.org/math/number-theory/lucas/
      https://oi-wiki.org/math/number-theory/crt/
标签: LeetCode第438场周赛, 组合数学, 欧拉定理, 扩展Lucas定理, 中国剩余定理, 组合数模非素数
*/

#include <bits/stdc++.h>

using namespace std;

const int MX = 5;
int c[MX][MX];

// 预处理组合数
auto init = []() {
    for (int i = 0; i < MX; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return 0;
}();

// 计算C(n, m) % p，要求p为质数
int lucas(int n, int m, int p) {
    if (m == 0) return 1;
    return c[n % p][m % p] * lucas(n / p, m / p, p) % p;
}

// 求C(n, m) % 10
int comb(int n, int m) {
    return 5 * lucas(n, m, 2) + 6 * lucas(n, m, 5);
}

class Solution3463 {
public:
    /* 灵茶题解另外一种解法，用扩展Lucas定理，
    把10分解成2和5，用Lucas定理求出C(n, m) % 2 和 % 5的值，
    然后由中国剩余定理，求出C(n, m) % 10，这里带入后是 C(n, m) mod 10 = (5r_2 + 6r_5) mod 10

    不算预处理的时间，这里每次计算comb时是重新算了，没有记忆化打表，时间复杂度O(nlogn)
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
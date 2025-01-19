/*
url:  https://leetcode.cn/problems/count-number-of-texts/?envType=daily-question&envId=2025-01-19
参考: https://leetcode.cn/problems/count-number-of-texts/solutions/1477311/by-endlesscheng-gj8f/
相关: LeetCode70. 爬楼梯
标签: 分组循环
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MX = 1e5 + 1;
long long f[MX], g[MX]; // f[x]和g[x]分别对应楼梯长度为x的情况下，一次最多3步、4步的方案数

auto init = []() {
    f[0] = g[0] = 1;
    f[1] = g[1] = 1;
    f[2] = g[2] = 2;
    f[3] = g[3] = 4;
    for (int i = 4; i < MX; i++) {
        f[i] = (f[i - 1] + f[i - 2] + f[i - 3]) % MOD;
        g[i] = (g[i - 1] + g[i - 2] + g[i - 3] + g[i - 4]) % MOD;
    }
    return 0;
}();

class Solution2266 {
public:
    int countChar(int digit) { // 数字按键上字母的数量
        if (digit == 7 || digit == 9) return 4;
        return 3;
    }

    // 我的解法，执行用时108ms，这个记忆化可以提到全局，不需要每次Solution对象都要重新算一遍，因为和输入pressedKeys无关
    int countTexts(string pressedKeys) {
        int n = pressedKeys.size();
        int mod = 1e9 + 7;
        vector<long long> fac;
        unordered_map<long long, long long> memo;
        int N = 1e5 + 1; // 1 <= pressedKeys.length <= 10^5

        auto calc = [&](auto& calc, int size, int count) { // size个小球，每隔count必须放一块隔板，一共多少种情况
            if (size == 0) return 1LL;
            long long key = (long long)count * N + size;
            if (memo.count(key)) return memo[key];
            long long res = 0;
            for (int i = 1; i <= size && i <= count; i++) {
                res = (res + calc(calc, size - i, count)) % mod;
            }
            memo[key] = res;
            return res;
        };

        // 分组循环
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && pressedKeys[i] == pressedKeys[i - 1]; i++);
            // [start, i)为一段
            int size = i - start;
            fac.push_back(calc(calc, size, countChar(pressedKeys[start] - '0')));
        }
        long long ans = fac[0] % mod;
        for (int i = 1; i < fac.size(); i++) {
            ans = ans * fac[i] % mod;
        }
        return ans;
    }

    /* 灵茶山艾府解法，执行用时4ms。对于长度为size的段，假如字母数为3，则相当于每次爬1/2/3步阶梯，到达顶点的方案数，
    这是LeetCode70. 爬楼梯 */
    int countTexts_implementation2(string pressedKeys) {
        int n = pressedKeys.size();
        long long ans = 1;
        int size = 0;
        for (int i = 0 ; i < n; i++) {
            char c = pressedKeys[i];
            size++;
            if (i == pressedKeys.size() || pressedKeys[i + 1] != c) {
                if (c == '7' || c == '9') {
                    ans = ans * g[size] % MOD;
                }
                else ans = ans * f[size] % MOD;
                size = 0;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2266 solu;
    // cout << solu.countTexts("22233") << endl;
    // cout << solu.countTexts("222222222222222222222222222222222222") << endl;
    cout << solu.countTexts("55555555999977779555") << endl;
    cout << solu.countTexts_implementation2("55555555999977779555") << endl;
    return 0;
}
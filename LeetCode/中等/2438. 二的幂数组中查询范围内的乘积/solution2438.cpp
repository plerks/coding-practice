/*
url: https://leetcode.cn/problems/range-product-queries-of-powers/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2438 {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> power; // n中2的幂的幂次
        while (n) {
            power.push_back(__lg(n & -n));
            n &= n - 1;
        }

        vector<int> pre(power.size() + 1);
        for (int i = 0; i < power.size(); i++) pre[i + 1] = pre[i] + power[i];

        auto qpow = [&](long long a, long long b) {
            constexpr int MOD = 1e9 + 7;
            long long res = 1;
            while (b) {
                if (b & 1) res = res * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }
            return res;
        };

        vector<int> ans;
        for (auto &v : queries) {
            int l = v[0], r = v[1];
            ans.push_back(qpow(2, pre[r + 1] - pre[l - 1 + 1]));
        }

        return ans;
    }

    // 灵茶题解的解法是，对n的2的幂值的所有[left, right]组合，用dp打表出来，f[i][j] = f[i][j - 1] * power[j] % MOD。然后queries时直接查表。
};

int main(int argc, char const *argv[]) {
    Solution2438 solu;
    auto a = solu.productQueries(15, *new vector<vector<int>>{{0,1},{2,2},{0,3}});
    return 0;
}
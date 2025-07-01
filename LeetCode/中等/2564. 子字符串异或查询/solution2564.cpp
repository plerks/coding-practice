/*
url: https://leetcode.cn/problems/substring-xor-queries/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2564 {
public:
    /* val ^ first == second，两边再异或second，则 val ^ first ^ second = 0，即 val == first ^ second。
    关心的是queries的first ^ second (记t)，对每个t，去除前导0后，用kmp找在s中的第一个出现位置？
    否，1 <= s.length <= 10^4，1 <= queries.length <= 10^5，会超时。
    但是t的长度有限(<=32)，所以，把s的所有长度为l的子串都先处理出来放map里，然后t去查

    运行用时459ms
    */
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        unordered_map<string, pair<int, int>> map;
        for (int l = 1; l <= 32; l++) {
            for (int i = 0; i <= n - l; i++) {
                string sub = s.substr(i, l);
                if (!map.count(sub)) {
                    map[sub] = {i, i + l - 1};
                }
            }
        }
        vector<vector<int>> ans(queries.size(), {-1, -1});
        for (int i = 0; i < queries.size(); i++) {
            auto &q = queries[i];
            int t = q[0] ^ q[1];
            string st = bitset<32>(t).to_string();
            // cout << st << endl;
            auto index = st.find('1');
            st = st.substr(index == -1 ? st.size() - 1 : index);
            if (map.count(st)) {
                auto p = map[st];
                ans[i] = {p.first, p.second};
            }
        }
        return ans;
    }

    /* 灵茶题解写法，避免了很多用string的地方。
    首先，枚举s的子串时，0开头的可以忽略，此外，map可以改成<int, pair<int, int>>，枚举长度时固定左端点，然后x << 1再或上下一个char，
    就能得到固定左端点，长度 + 1的字符串对应的int值。
    此外 10^9 < 2^30，所以 q[0] ^ q[1] 最多30位。

    运行用时71ms
    */
    vector<vector<int>> substringXorQueries_implementation2(string s, vector<vector<int>>& queries) {
        int n = s.size();
        unordered_map<int, pair<int, int>> map;
        // 忽略0开头的会漏掉"0"，单独处理
        if (auto i = s.find('0'); i != -1) {
            map[0] = {i, i};
        }
        for (int l = 0; l < n; l++) {
            if (s[l] == '0') continue;
            for (int r = l, x = 0; r < min(l + 30, n); r++) {
                x = (x << 1) | (s[r] - '0');
                if (!map.count(x)) map[x] = {l, r};
            }
        }

        vector<vector<int>> ans(queries.size(), {-1, -1});
        for (int i = 0; i < queries.size(); i++) {
            auto &q = queries[i];
            int t = q[0] ^ q[1];
            if (map.count(t)) {
                auto p = map[t];
                ans[i] = {p.first, p.second};
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2564 solu;
    auto a = solu.substringXorQueries("101101", *new vector<vector<int>>{{0,5},{1,2}});

    auto b = solu.substringXorQueries_implementation2("101101", *new vector<vector<int>>{{0,5},{1,2}});
    return 0;
}
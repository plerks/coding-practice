/*
url: https://leetcode.cn/problems/find-the-count-of-good-integers/description/
LeetCode参考: https://leetcode.cn/problems/find-the-count-of-good-integers/solutions/2899725/mei-ju-suo-you-hui-wen-shu-zu-he-shu-xue-3d35/
标签: 排列, 组合数学
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3272 {
public:
    // 我的解法，能通过，但是用时高，1861ms。枚举所有n位的回文数的成分，然后排列组合计算个数
    long long countGoodIntegers(int n, int k) {
        unordered_map<int, int> map;
        long long ans = 0;

        unordered_set<string> set;

        auto calc = [&](unordered_map<int, int> digit_map) {
            // 先选一个非0的排首位，然后剩下的全排，然后再除以每个数字的全排列
            for (auto p : digit_map) {
                if (p.first == 0) {
                    continue;
                }

                digit_map[p.first]--; // 这一轮p.first排首位
                
                long long count = A(n - 1, n - 1);
                for (auto &p : digit_map) {
                    count /= A(p.second, p.second);
                }

                ans += count;
                digit_map[p.first]++;
            }
        };

        // num的合法重排都是好整数
        auto dfs = [&](auto &dfs, int p, long long num) -> void {
            if (p > n - 1 - p) {
                if (num % k == 0) {
                    string s;
                    for (int i = 0; i <= 9; i++) {
                        if (map.count(i)) {
                            s = to_string(map[i]) + '_' + s;
                        }
                        else s = "0_" + s;
                    }
                    set.insert(s);
                }
                return;
            }
            int lo = (p == 0) ? 1 : 0;
            for (int i = lo; i <= 9; i++) { // 这一位上填i
                if (p == n - 1 - p) {
                    map[i]++;
                    dfs(dfs, p + 1, num + i * pow(10, p));
                    map[i]--;
                    if (map[i] == 0) map.erase(i);
                }
                else {
                    map[i] += 2;
                    dfs(dfs, p + 1, num + i * pow(10, p) + i * pow(10, n - 1 - p));
                    map[i] -= 2;
                    if (map[i] == 0) map.erase(i);
                }
            }
        };

        dfs(dfs, 0, 0); // 找出所有回文数的成分，然后重排

        for (auto &s : set) {
            unordered_map<int, int> digit_map;
            int x = 9;
            int count = 0;
            for (char c : s) {
                if (c == '_') {
                    if (count > 0) digit_map[x] = count;
                    x--;
                    count = 0;
                }
                else {
                    count = count * 10 + (c - '0');
                }
            }
            calc(digit_map);
        }

        return ans;
    }

    int C(int n, int m) {
        return A(n, n) / A(m, m) / A(n - m, n - m);
    }

    int A(int n, int m) {
        int res = 1;
        for (int i = 0; i < m; i++) {
            res *= n - i;
        }
        return res;
    }

    // 灵茶山艾府题解解法，515ms
    long long countGoodIntegers_implementation2(int n, int k) {
        // 预处理阶乘
        vector<int> factorial(n + 1);
        factorial[0] = 1;
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        long long ans = 0;

        unordered_set<string> set;
        int m = (n + 1) / 2;
        // 枚举回文数的左半边，从[10^(m - 1), 10^m]
        for (int x = pow(10, m - 1); x < pow(10, m); x++) {
            string s = to_string(x);
            s += string(s.rbegin() + (n % 2), s.rend());
            if (stoll(s) % k == 0) {
                sort(s.begin(), s.end());
                set.insert(s);
            }
        }
        for (auto &s : set) {
            int count[10]{};
            for (char c : s) count[c - '0']++;
            // 合法排列总数为 选任一非0数放首位，剩下n - 1个全排，然后除以各个数字的内部全排
            int res = n - count[0];
            res *= factorial[n - 1];
            for (int i = 0; i <= 9; i++) {
                res /= factorial[count[i]];
            }
            ans += res;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3272 solu;
    cout << solu.countGoodIntegers(3, 5) << endl;
    cout << solu.countGoodIntegers_implementation2(3, 5) << endl;
    return 0;
}

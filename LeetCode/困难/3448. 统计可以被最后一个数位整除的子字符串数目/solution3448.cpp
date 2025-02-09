/*
url: https://leetcode.cn/problems/count-substrings-divisible-by-last-digit/
参考: https://leetcode.cn/problems/count-substrings-divisible-by-last-digit/solutions/3068623/gong-shi-tui-dao-dong-tai-gui-hua-python-iw4a/
标签: LeetCode第436场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3448 {
public:
    /* 周赛时想到了关键点，但是没写出来。这题的关键点是，枚举子串右端点，
    对于前面的数，其会 * 10，为了找到当前 mod d == 0的个数，需要计数以上一个位置为末尾的子串取模的余数，
    然后用取模的性质计算新的余数。
    */
    long long countSubstrings(string s) {
        int n = s.size();
        long long ans = 0;
        // 代表到当前位置，mod m 的余数是j的子串个数，每轮需要有cnt和newCnt两个数组，用滚动数组，直接每次创建个newCnt然后计算会超时
        vector<vector<vector<long long>>> arr(2, vector<vector<long long>>(10, vector<long long>(10, 0)));
        for (int i = 0; i < n; i++) { // 枚举右端点
            int d = s[i] - '0';
            for (int m = 1; m <= 9; m++) {
                for (int j = 0; j <= 9; j++) {
                    // 初始化newCnt
                    arr[(i + 1) & 1][m][j] = 0;
                }
            }
            for (int m = 1; m <= 9; m++) {
                for (int j = 0; j <= 9; j++) {
                    arr[(i + 1) & 1][m][(10 * j + d) % m] += arr[i & 1][m][j]; // 类似贡献法中的刷表法，不知道要? * 10 % m == x，?是多少，但是可以用?计算刷表
                }
            }
            for (int m = 1; m <= 9; m++) {
                arr[(i + 1) & 1][m][d % m]++;
            }
            if (d != 0) ans += arr[(i + 1) & 1][d][0];
        }
        return ans;
    }

    /* 灵茶题解写法，更简洁，这里cnt和newCnt得用array，用array 247ms，用vector 2670ms，常数差距很大
    */
    long long countSubstrings_implementation2(string s) {
        int n = s.size();
        long long ans = 0;
        array<int, 9> cnt[10]{}; // 代表到当前位置，mod m 的余数是j的子串个数，m最多为9，则j最多为8
        for (int i = 0; i < n; i++) { // 枚举右端点
            int d = s[i] - '0';
            for (int m = 1; m <= 9; m++) {
                array<int, 9> newCnt{};
                newCnt[d % m]++;
                for (int j = 0; j < m; j++) {
                    newCnt[(10 * j + d) % m] += cnt[m][j];
                }
                cnt[m] = newCnt;
            }
            ans += cnt[d][0];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3448 solu;
    cout << solu.countSubstrings("12936") << endl;
    cout << solu.countSubstrings_implementation2("12936") << endl;
    return 0;
}
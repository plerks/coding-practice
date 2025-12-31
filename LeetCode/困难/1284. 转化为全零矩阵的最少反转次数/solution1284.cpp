/*
url: https://leetcode.cn/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/
参考: https://leetcode.cn/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/solutions/101359/zhuan-hua-wei-quan-ling-ju-zhen-de-zui-shao-fan-2/
标签: 【题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1284 {
public:
    // 时间复杂度 O(mn * 2^{mn})，矩阵共有 2^{mn} 种状态，每种状态都会跑一个 mn 的循环
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        // 1 <= m, n <= 3，算到0的距离
        unordered_set<int> vis;

        auto get_mask = [&]() {
            int mask = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = i * n + j;
                    if (mat[i][j] == 1) mask |= 1 << pos;
                }
            }
            return mask;
        };

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int x, int y) {
            return 0 <= x && x < m && 0 <= y && y < n;
        };

        auto bfs = [&]() {
            int mask = get_mask();
            if (mask == 0) return 0;
            queue<int> q;
            unordered_set<int> st;
            q.push(mask);
            st.insert(mask);
            int level = 1;
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; i++) {
                    int cur = q.front(); q.pop();
                    // 枚举flip每个位置
                    for (int i = 0; i < m * n; i++) {
                        int new_mask = cur;
                        int x = i / n, y = i % n;
                        new_mask = cur ^ (1 << (x * n + y));
                        for (auto& [dx, dy] : directions) {
                            int xx = x + dx, yy = y + dy;
                            if (legal(xx, yy)) {
                                int pos = xx * n + yy;
                                new_mask = new_mask ^ (1 << pos);
                            }
                        }
                        if (new_mask == 0) return level;
                        if (!vis.count(new_mask)) {
                            q.push(new_mask);
                            vis.insert(new_mask);
                        }
                    }
                }
                level++;
            }
            return -1; // 搜索不到0
        };
        
        return bfs();
    }

    /* 参考官方题解，一个位置要么翻转一次，要么不翻转，多余的翻转是无效的，因此，枚举第一行的翻转方式，然后对于第二行，看第一行
    若上面的第一行对应位置为1，则第二行的此位置则必须翻转，否则必须不翻转。直到最后一行根据上一行的情况翻转后，看自己是否为全0，则
    知道能否把整个矩阵翻转成全0。
    也就是说只需要枚举第一行的所有情况，后面的行逐行确定。

    时间复杂度 O(mn * 2^n)，枚举第一行的 n 个位置的 2^n 种情况，对于每种情况要花 O(mn) 时间跑一遍矩阵
    */
    int minFlips_implementation2(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        auto get_mask = [&]() {
            int mask = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int pos = i * n + j;
                    if (mat[i][j] == 1) mask |= 1 << pos;
                }
            }
            return mask;
        };

        int mask = get_mask(); // 初始矩阵状态

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int x, int y) {
            return 0 <= x && x < m && 0 <= y && y < n;
        };

        int ans = INT_MAX;

        for (int f = 0; f < (1 << n); f++) { // 第一行翻转方式的枚举
            int cur = mask;
            int cnt = 0; // 翻转次数
            for (int i = 0; i < n; i++) {
                if ((f >> i) & 1) {
                    // 在(0, y) 位置上flip
                    int x = 0, y = i % n;
                    cur = cur ^ (1 << (x * n + y));
                    cnt++;
                    for (auto& [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy)) {
                            int pos = xx * n + yy;
                            cur = cur ^ (1 << pos);
                        }
                    }
                }
            }
            // 第一行已依照 f 的状态 flip 完毕

            for (int x = 1; x < m; x++) {
                for (int y = 0; y < n; y++) {
                    int ppos = (x - 1) * n + y; // (x - 1, y) 在 cur 中的位置
                    if ((cur >> ppos) & 1) {
                        // 要在(x, y) 位置上flip
                        cur = cur ^ (1 << (x * n + y));
                        cnt++;
                        for (auto& [dx, dy] : directions) {
                            int xx = x + dx, yy = y + dy;
                            if (legal(xx, yy)) {
                                int pos = xx * n + yy;
                                cur = cur ^ (1 << pos);
                            }
                        }
                    }
                }
            }
            
            // 检查最后一行是否全为 0
            bool ok = true;
            for (int j = 0; j < n; j++) {
                int pos = (m - 1) * n + j;
                if ((cur >> pos) & 1) ok = false;
            }
            if (ok) ans = min(ans, cnt);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1284 solu;
    cout << solu.minFlips(*new vector<vector<int>>{{0,0},{0,1}}) << endl;
    cout << solu.minFlips_implementation2(*new vector<vector<int>>{{0,0},{0,1}}) << endl;
    return 0;
}
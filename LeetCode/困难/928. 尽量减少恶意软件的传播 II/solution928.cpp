/*
url: https://leetcode.cn/problems/minimize-malware-spread-ii/
相关: LeetCode924. 尽量减少恶意软件的传播
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution928 {
public:
    // 此题为无向图，graph[i][j] == graph[j][i]
    /* 参考灵茶题解，
    如何找只会被一个initial节点污染的节点？
    dfs，从未被污染的节点dfs。dfs能被污染节点挡住，然后dfs完后看找到的initial节点情况
    */
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        unordered_set<int> st(initial.begin(), initial.end());
        
        vector<int> vis(n);
        int state; // -1代表没碰到污染节点，-2代表碰到多个，>=0代表碰到一个，且值为节点编号
        int size;

        auto dfs = [&](auto& dfs, int x) -> void {
            vis[x] = true;
            size++;
            for (int y = 0; y < n; y++) {
                if (graph[x][y] == 0) continue;
                if (st.count(y)) { // y是被污染的，不由它继续dfs，只更新状态
                    if (state == -1) state = y;
                    else if (state >= 0) if (state != y) state = -2; // 遇到第二种污染节点，注意不是第二个，可能有多条路径到一个污染点
                }
                else if (!vis[y]) dfs(dfs, y);
            }
        };

        vector<int> cnt(n); // 删除i能不被污染的节点数
        for (int i = 0; i < n; i++) {
            if (vis[i] || st.count(i)) continue;
            state = -1;
            size = 0;
            dfs(dfs, i);
            if (state >= 0) {
                cnt[state] += size; // 这个连通分量只会碰到state这个节点，将分量大小加入state的cnt计数
            }
        }

        int mx = -1;
        int ans = -1;
        for (int x : initial) {
            int c = cnt[x];
            /* if (c > mx) {
                mx = c;
                ans = x;
            }
            else if (c == mx) ans = min(ans, x); */
            // 更简洁的写法：
            if (c > mx || (c == mx && x < ans)) {
                mx = c;
                ans = x;
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution928 solu;
    // cout << solu.minMalwareSpread(*new vector<vector<int>>{{1,1,0},{1,1,0},{0,0,1}}, *new vector<int>{0,1});
    cout << solu.minMalwareSpread(*new vector<vector<int>>{{1,1,0},{1,1,1},{0,1,1}}, *new vector<int>{0,1});
    return 0;
}
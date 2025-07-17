/*
url: https://leetcode.cn/problems/longest-cycle-in-a-graph/
参考: https://leetcode.cn/problems/longest-cycle-in-a-graph/solutions/1710828/nei-xiang-ji-huan-shu-zhao-huan-li-yong-pmqmr/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2360 {
public:
    // 有环的话，跟着走一定能发现
    // 不过题目是每个节点 至多 有一条出边，不一定是基环树，整个图可能不连通。每个分量是个基环树或者干脆没有环
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        int ans = -1;
        vector<int> vis(n);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                ans = max(ans, circle_len(edges, vis, i));
            }
        }
        return ans;
    }

    int circle_len(vector<int>& edges, vector<int>& vis, int cur) {
        unordered_map<int, int> st; // (值，位置)
        int cnt = 0;
        while (cur != -1) {
            if (st.count(cur)) { // 找到环
                return cnt - st[cur];
            }
            if (vis[cur]) break;
            vis[cur] = true;
            st.insert({cur, cnt++});
            cur = edges[cur];
        }
        return -1;
    }

    /* 参考灵茶题解，用发现时间来标记。
    此外，灵茶题解里的注释：
        本题保证每个连通块至多有一个环，所以可以根据时间差算出环长。如果没有这个保证，时间差算出的可能不是最长环。一般图的最长环是 NP-hard 问题。
    */
    int longestCycle_implementation2(vector<int>& edges) {
        int n = edges.size();
        int ans = -1;
        int time = 0; // 当前时间
        vector<int> vis_time(n, -1); // 发现时间
        for (int i = 0; i < n; i++) {
            int start_time = time;
            int x = i; // 当前节点
            while (x != -1 && vis_time[x] == -1) { // 未访问过，接着路走
                vis_time[x] = time++;
                x = edges[x];
            }

            // vis_time[x] >= start_time 是为了保证，到达的点x是由start_time开始的走连通分量过程发现的，而不是后面的x发现的。（识别后向边，排除跨边）
            if (x != -1 && vis_time[x] >= start_time) { // x走到了终点或发现环
                ans = max(ans, time - vis_time[x]);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2360 solu;
    cout << solu.longestCycle(*new vector<int>{3,3,4,2,3}) << endl;
    cout << solu.longestCycle(*new vector<int>{1,2,0,4,5,6,3,8,9,7}) << endl;

    cout << solu.longestCycle_implementation2(*new vector<int>{3,3,4,2,3}) << endl;
    cout << solu.longestCycle_implementation2(*new vector<int>{1,2,0,4,5,6,3,8,9,7}) << endl;
    return 0;
}
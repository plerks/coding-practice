/*
url: https://leetcode.cn/problems/find-closest-node-to-given-two-nodes/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2359 {
public:
    /* 每个节点 至多 有一条出边。可能是基环树，也可能没有环。
    不管如何，至多一条出边，从一个点开始走，下一步只有一种可能
    */
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<int> dis1 = get_path(edges, node1);
        vector<int> dis2 = get_path(edges, node2);
        int min_dis = INT_MAX;
        int ans = INT_MAX; // 如果有多个答案，返回最小的节点编号
        for (int i = 0; i < n; i++) {
            if (dis1[i] != INT_MAX && dis2[i] != INT_MAX) {
                int t = max(dis1[i], dis2[i]);
                if (t < min_dis || (t == min_dis && i < ans)) {
                    min_dis = t;
                    ans = i;
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }

    // 获取基环树node到其它点的距离
    vector<int> get_path(vector<int>& edges, int node) {
        int n = edges.size();
        vector<int> vis(n); // 可以用 dis == INT_MAX 来省下 vis
        vector<int> dis(n, INT_MAX);
        int cur = node;
        int d = 0;
        while (cur != -1 && !vis[cur]) {
            dis[cur] = d++;
            vis[cur] = true;
            cur = edges[cur];
        }
        return dis;
    }

    /* 参考灵茶题解，文艺灵神之方法二：「我吹过你吹过的晚风」。很符合这个解法的名字
    让node1和node2同步一步一步地走，如果二者走到过相同的节点，则那个节点为ans。
    如果node1和node2同时走到了对方走到过的点，则返回小者。
    
    注意必须让 x 和 y 同步走，不能先把 x 和 y 的path求出来，然后把一个作为set，然后遍历另一者的path节点，
    然后第一次发现在set中的节点则返回其作为ans。
    反例，节点2和节点3的路径分别为：
    2：2 1 3 0 5 4
    3：3 0 5 4 2 1
    如果把3的path作为set，然后遍历2的set，会返回2，而非正确值3。原因在于2在节点3的路径中太靠后了，不能一开始就整个把3的path作为set，要动态维护。
    */
    int closestMeetingNode_implementation2(vector<int>& edges, int x, int y) {
        int n = edges.size();
        vector<int> vis_x(n);
        vector<int> vis_y(n);
        int ans = n;

        while (!vis_x[x] || !vis_y[y]) {
            vis_x[x] = vis_y[y] = true;

            if (vis_x[y]) { // y走到了x曾在的位置
                ans = y;
            }
            if (vis_y[x]) { // y走到x曾在的位置 和 x走到y曾在的位置 同时发生
                ans = min(ans, x);
            }
            if (ans < n) { // 找到了答案
                return ans;
            }
            if (edges[x] != -1) x = edges[x];
            if (edges[y] != -1) y = edges[y];
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2359 solu;
    cout << solu.closestMeetingNode(*new vector<int>{2,2,3,-1}, 0, 1) << endl;
    cout << solu.closestMeetingNode(*new vector<int>{1,2,-1}, 0, 2) << endl;
    cout << solu.closestMeetingNode(*new vector<int>{5,3,1,0,2,4,5}, 3, 2) << endl;

    cout << solu.closestMeetingNode_implementation2(*new vector<int>{2,2,3,-1}, 0, 1) << endl;
    cout << solu.closestMeetingNode_implementation2(*new vector<int>{1,2,-1}, 0, 2) << endl;
    cout << solu.closestMeetingNode_implementation2(*new vector<int>{5,3,1,0,2,4,5}, 3, 2) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/description/
LeetCode参考: https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/solutions/2229503/lei-si-da-jia-jie-she-iii-pythonjavacgo-4k3wq/
              https://leetcode.cn/problems/minimize-the-total-price-of-the-trips/solutions/2553222/zui-xiao-hua-lu-xing-de-jie-ge-zong-he-b-6al2/
相关: LeetCode337. 打家劫舍 III, LeetCode2846. 边权重均等查询
标签: 树状dp，Tarjan算法, 树上差分, 树中节点路径, 最近公共祖先
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2646 {
public:
    /* 一个错误的想法，137 / 407 个通过的测试用例，解答错误。
    节点减半可以尽可能贪心，因此以0为根，0有减半/不减半两种情况，要求不能相邻减半，因此贪心地隔一个节点减半，0确定
    后其它节点也就确定了。
    也就是把偶数层节点全减半/把奇数层节点全减半两种情况，然后对trip dfs求路径和。
    这样做的错误之处在于，比如1000-1-1-1000这种情况，可以舍弃中间的隔一个节点的贪心，将两头都减半以获得更好的情况，
    而隔一个节点贪心考虑不到这种情况。 */
    int minimumTotalPrice_wrong(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<int>> graph(n, vector<int>());
        for (int i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }
        queue<int> q;
        q.push(0);
        int depth = 0;
        vector<int> depths(n, 0);
        vector<int> visited(n, 0);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int node = q.front();
                visited[node] = true;
                depths[node] = depth;
                for (int j = 0; j < graph[node].size(); j++) {
                    if (visited[graph[node][j]]) continue;
                    q.push(graph[node][j]);
                }
                q.pop();
            }
            depth++;
        }
        vector<vector<int>> cost(n, vector<int>(n, INT_MAX));
        vector<int> price1 = price;
        for (int i = 0; i < price1.size(); i++) {
            if (depths[i] % 2 == 0) price1[i] /= 2;
        }
        vector<int> price2 = price;
        for (int i = 0; i < price2.size(); i++) {
            if (depths[i] % 2 == 1) price2[i] /= 2;
        }
        // 1 <= trips.length <= 100，较小，不提前算各个节点对的最小距离，直接一个一个dfs
        int total1 = 0; // 偶数层节点减半
        for(int i = 0; i < trips.size(); i++) {
            vector<int>& v = trips[i];
            total1 += dfs(v[0], v[1], graph, price1, -1, 0);
        }
        int total2 = 0; // 奇数层节点减半
        for(int i = 0; i < trips.size(); i++) {
            vector<int>& v = trips[i];
            total2 += dfs(v[0], v[1], graph, price2, -1, 0);
        }
        return min(total1, total2);
    }

    int dfs(int s, int d, vector<vector<int>>& graph, vector<int>& price, int parent, int sum) {
        sum += price[s];
        if (s == d) return sum;
        int distance = INT_MAX;
        for (int child : graph[s]) {
            if (child == parent) continue;
            distance = min(distance, dfs(child, d, graph, price, s, sum));
        }
        return distance;
    }

    // 参考灵茶山艾府题解，对trips所有经过的点计数，然后类似`LeetCode 337. 打家劫舍 III`，对节点分减半与不减半进行dp
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<int>> graph(n, vector<int>());
        for (auto &edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        // dfs计算每个节点需要被访问的次数
        vector<int> count(n);
        for (auto &trip : trips) {
            dfs2(graph, trip[0], trip[1], count, -1);
        }
        // dp，以0为根
        pair<int, int> p = dpDfs(graph, 0, count, -1, price);
        /* 灵茶山艾府题解里用了lambda表达式来实现定义这里的dfs2()和dpDfs()函数，参数就不用这么多。
        这里如果把graph,count,price这些变量弄成成员变量也不用传这么多参数，但是定义为指针写起来麻烦，定义为
        直接的对象又要发生复制，没Java那么方便。 */
        return min(p.first, p.second);
    }

    bool dfs2(vector<vector<int>>& graph, int s, int d, vector<int>& count, int parent) {
        if (s == d) {
            count[s]++;
            return true;
        }
        else {
            for (int child : graph[s]) {
                if (child == parent) continue;
                if (dfs2(graph, child, d, count, s)) { // 在递归的"归"的过程中计数
                    count[s]++;
                    return true;
                }
            }
        }
        return false;
    }

    // 类似LeetCode337. 打家劫舍 III，pair.first表示选root的最小值，pair.second表示不选root的最小值
    pair<int, int> dpDfs(vector<vector<int>>& graph, int root, vector<int>& count, int parent, vector<int>& price) {
        int halve = price[root] * count[root] / 2; // root减半
        int notHalve = price[root] * count[root]; // root不减半
        for (int child : graph[root]) {
            if (child != parent) {
                pair<int, int> p = dpDfs(graph, child, count, root, price);
                halve += p.second; // x减半的情况下，只能选择儿子不减半的情况
                notHalve += min(p.first, p.second); // x未减半，则儿子可以选择减半或不减半
            }
        }
        return {halve, notHalve};
    }

    // 待做: 这题还有用Tarjan算法的做法
};

int main(int argc, char const *argv[]) {
    Solution2646 solu;
    vector<vector<int>> edge = {{0,1},{1,2},{1,3}};
    vector<int> price = {2,2,10,6};
    vector<vector<int>> trips = {{0,3},{2,1},{2,3}};
    /* 如果这里写cout << solu.minimumTotalPrice(4, vector<vector<int>>{{0,1},{1,2},{1,3}}, vector<int>{2,2,10,6}, vector<vector<int>>{{0,3},{2,1},{2,3}}) << endl;
    会报错把左值引用绑定到右值上，commonDataStructure.cpp中有类似的情况，一个解决方式是把minimumTotalPrice()的参数声明为常左值引用，例如const vector<vector<int>>& edges */
    cout << solu.minimumTotalPrice(4, edge, price, trips) << endl;
    return 0;
}
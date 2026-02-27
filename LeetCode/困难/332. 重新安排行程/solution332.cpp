/*
url: https://leetcode.cn/problems/reconstruct-itinerary/
参考: https://leetcode.cn/problems/reconstruct-itinerary/solutions/389885/zhong-xin-an-pai-xing-cheng-by-leetcode-solution/
      https://oi-wiki.org/graph/euler/
标签: Hierholzer 算法
*/
#include <bits/stdc++.h>

using namespace std;

/* 参考官方题解，
题目保证存在路径，因此图一定是欧拉图或者半欧拉图，起点已由题目固定为 "JFK"
去 dfs 的话，有一个节点是特殊的，就是(可能存在的)那个入度与出度差为 1 的节点会导致死胡同，
dfs 会回不来，但是如果存在这种节点，其必是最后遍历的节点。
假如是 u -> v ， u <-> w ， v 是末端，dfs(u) 时，不能按先序把 u v 加到 ans 里，因为是不能实现 u v w u 的访问顺序的，
正确访问应当是 u w u v ，要按后序把 root 加到 ans 里，得到 v u w u 再把结果反向，刚好是 ans。（而且如果对 u 的邻居先访问 w 也会是对的）
*/
class Solution332 {
public:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> g; // 为了得到字典序最小的欧拉路径，将边排序
    vector<string> st;

    void dfs(const string& root) {
        while (g.count(root) && g[root].size() > 0) {
            string nbr = g[root].top(); g[root].pop(); // 删已访问的边
            dfs(nbr);
        }
        st.emplace_back(root);
    }

    vector<string> findItinerary(vector<vector<string>>& edges) {
        for (auto& e : edges) {
            g[e[0]].emplace(e[1]); // 有向图
        }
        dfs("JFK");
        reverse(st.begin(), st.end());
        return st;
    }
};

int main(int argc, char const *argv[]) {
    Solution332 solu;
    auto a = solu.findItinerary(*new vector<vector<string>>{{"JFK","2"},{"2","3"},{"3","2"}});
    return 0;
}
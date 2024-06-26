/*
url: https://leetcode.cn/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/description/
LeetCode参考: https://leetcode.cn/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/solutions/2553195/zhong-xin-gui-hua-lu-xian-by-leetcode-so-psl6/
标签: 进制表示法, dfs
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1466 {
public:
    /* 我的解法。给的是树结构，以0为根dfs，若发现边的方向不对，将其反向，为了dfs能到达反向的节点，需要把边当作无向边处理，
    用unordered_set来记录边的原始方向。LeetCode执行用时459ms。 */
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        /* 用unordered_set<int>，LeetCode上有一个用例会报错:
        runtime error: signed integer overflow: 45988 * 46697 cannot be represented in type 'int' (solution.cpp)
        SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:16:34
        应该是对应mySet.insert(edge[0] * n + edge[1])这行。
        直接windows下测试`int c1, c2; cin >> c1 >> c2; int c = c1 * c2;`是不会报错的，溢出就溢出了。
        这里sanitizer是gcc/g++的一个编译选项，加上之后可以检查地址错误，未定义行为等问题，例如
        `g++ -g -fsanitize=undefined test.cpp -o test`，这里溢出是ub，LeetCode后台运行时加上了sanitizer，所以会检测并报错。
        实测ubuntu下的g++可以直接用sanitizer，windows下mingw的g++不行。
        */
        unordered_set<long long> mySet;
        for (auto &edge : connections) {
            // 用进制表示法，C++里unordered_set<pair<int, int>>和Java HashSet<int[]>一样，不是默认可哈希的
            mySet.insert(edge[0] * (long long)n + edge[1]);
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        return dfs(0, graph, -1, mySet);
    }

    int dfs(int root, vector<vector<int>>& graph, int parent, unordered_set<long long>& set) {
        int ans = 0;
        int n = graph.size();
        for (int child : graph[root]) {
            if (child != parent) {
                if (set.count(root * (long long)n + child)) {
                    ans++;
                }
                ans += dfs(child, graph, root, set);
            }
        }
        return ans;
    }

    // 官方题解的解法，思路相同，细节上直接建图时标记边的方向，避免用unordered_set。LeetCode执行用时240ms。
    int minReorder_implementation2(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &edge : connections) {
            graph[edge[0]].push_back(make_pair(edge[1], 1)); // 原方向的边，用1标记
            graph[edge[1]].push_back(make_pair(edge[0], 0)); // 把图变为无向图以做dfs
        }
        return dfs(0, graph, -1);
    }

    int dfs(int root, vector<vector<pair<int, int>>>& graph, int parent) {
        int ans = 0;
        for (auto &edge : graph[root]) {
            if (edge.first != parent) {
                ans += edge.second + dfs(edge.first, graph, root);
            }
        }
        return ans;
    }

    // 这题LeetCode官方题解的C++代码执行用时280ms，官方题解的Java代码执行用时32ms
};

int main(int argc, char const *argv[]) {
    Solution1466 solu;
    vector<vector<int>> connections = {{0,1},{1,3},{2,3},{4,0},{4,5}};
    cout << solu.minReorder(6, connections) << endl;
    cout << solu.minReorder_implementation2(6, connections) << endl;
    return 0;
}

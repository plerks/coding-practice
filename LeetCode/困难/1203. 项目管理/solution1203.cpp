/*
url: https://leetcode.cn/problems/sort-items-by-groups-respecting-dependencies/
参考: https://leetcode.cn/problems/sort-items-by-groups-respecting-dependencies/solutions/556357/xiang-mu-guan-li-by-leetcode-solution-3e7j/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1203 {
public:
    /* 参考官方题解，这题要把items拓扑排序，但是此题要求items要按组来分，不能达到的话返回空数组。所以
    要先把group拓扑排序，然后组内将items排序。
    组间的拓扑排序怎么做？
    根据items的依赖关系，若item1和item2有依赖关系，则item1所属的组g1和item2所属的组g2就有依赖关系。
    一个item可能不属于任何小组，但是仍然可能别的item需要依赖其先完成，还是会有人去完成这类任务，
    所以，要将没有所属的item分配个组号，最多会出现n + m个组号，这样每个item有个组，但一些组可能为空，然后统一对各个组先拓扑排序。
    */
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // n 个 item ，m 个原始的 group
        vector<vector<int>> group_item(n + m); // 每个组内有哪些item

        vector<vector<int>> group_graph(n + m); // 组之间的依赖关系
        vector<vector<int>> item_graph(n); // item之间的依赖关系

        int alloc_group_id = m; // 分配组号
        for (int i = 0; i < group.size(); i++) {
            if (group[i] == -1) {
                group[i] = alloc_group_id++; // i号item所属的组为alloc_group_id
            }
            group_item[group[i]].push_back(i);
        }
        // 每个item所属的组号可以通过group获取

        vector<int> group_indeg(n + m);
        vector<int> item_indeg(n);

        for (int i = 0; i < n; i++) {
            auto &vec = beforeItems[i]; // 每个item的前置item
            for (int j : vec) {
                int group_i = group[i];
                int group_j = group[j];
                // 注意!: group_graph只记录了组间的边，item_graph只记录了组内的边
                // 这样就可以先拓扑排序组之间，再组之内
                if (group_i != group_j) {
                    group_graph[group_j].push_back(group_i);
                    group_indeg[group_i]++;
                }
                else {
                    item_graph[j].push_back(i);
                    item_indeg[i]++;
                }
            }
        }

        vector<int> ans;

        vector<int> all_group_id(n + m);
        iota(all_group_id.begin(), all_group_id.end(), 0);
        vector<int> res = topo_order(group_graph, group_indeg, all_group_id);
        if (res.empty()) return {}; // 组之间没有拓扑序
        for (int group_id : res) {
            if (group_item[group_id].empty()) continue; // 组内没有任务，跳过，不然topo_order是靠返回的vec是否为空判断有无拓扑序的，不跳过辨别不了了
            vector<int> res = topo_order(item_graph, item_indeg, group_item[group_id]);
            if (res.empty()) return {}; // 此组内没有拓扑序
            for (int item : res) ans.push_back(item);
        }

        return ans;
    }

    // 对g中elem的元素进行拓扑排序。返回拓扑序，若拓扑序不存在则返回空数组
    // 这个函数复用，既用于组间拓扑排序，也用于组内拓扑排序
    vector<int> topo_order(vector<vector<int>>& g, vector<int>& indeg, vector<int>& elem) {
        int n = indeg.size(); // 所有节点
        // elem为此轮涉及到的节点
        queue<int> q;
        for (int e : elem) {
            if (indeg[e] == 0) q.push(e); // 用于组内拓扑排序时，由于组件的边是被砍断的了，所以只引入当前组内的点到q里，就能完成此组的拓扑排序
        }

        vector<int> res;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            res.push_back(x);
            for (int y : g[x]) {
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);
            }
        }

        if (res.size() != elem.size()) return {};
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution1203 solu;
    auto a = solu.sortItems(8, 2, *new vector<int>{-1,-1,1,0,0,1,0,-1},
                                *new vector<vector<int>>{{},{6},{5},{6},{3,6},{},{},{}});
    return 0;
}
/*
url: https://leetcode.cn/problems/keys-and-rooms/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution841 {
public:
    // 这是个搜索问题，也能用bfs
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> vis(n);
        int cnt = n; // 未拿到钥匙的房间数
        unordered_set<int> keys;
        keys.insert(0);

        auto dfs = [&](auto& dfs, int i) -> void {
            cnt--;
            vis[i] = true;
            for (int key : rooms[i]) {
                if (!vis[key]) dfs(dfs, key);
            }
        };

        dfs(dfs, 0);

        return cnt == 0;
    }
};

int main(int argc, char const *argv[]) {
    Solution841 solu;
    cout << solu.canVisitAllRooms(*new vector<vector<int>>{{1},{2},{3},{}}) << endl;
    cout << solu.canVisitAllRooms(*new vector<vector<int>>{{1,3},{3,0,1},{2},{0}}) << endl;
    return 0;
}
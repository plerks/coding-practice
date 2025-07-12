/*
url: https://leetcode.cn/problems/get-watched-videos-by-your-friends/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1311 {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int k) {
        int n = watchedVideos.size();
        auto& g = friends;
        queue<int> q;
        vector<int> vis(n);
        q.push(id);
        vis[id] = true;
        for (int level = 0; !q.empty(); level++) {
            int size = q.size();
            if (level == k) break; // 此时q中为level层的节点
            for (int i = 0; i < size; i++) {
                int x = q.front(); q.pop();
                for (int y : g[x]) {
                    if (!vis[y]) {
                        q.push(y);
                        vis[y] = true;
                    }
                }
            }
        }

        unordered_map<string, int> map;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (auto& s : watchedVideos[x]) map[s]++;
        }
        vector<pair<int, string>> temp;
        for (auto& [s, c] : map) {
            temp.emplace_back(c, s);
        }
        sort(temp.begin(), temp.end());
        
        vector<string> ans;
        for (auto& [c, s] : temp) ans.push_back(s);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1311 solu;
    auto a = solu.watchedVideosByFriends(*new vector<vector<string>>{{"A","B"},{"C"},{"B","C"},{"D"}},
                                            *new vector<vector<int>>{{1,2},{0,3},{0,3},{1,2}}, 0, 1);
    return 0;
}
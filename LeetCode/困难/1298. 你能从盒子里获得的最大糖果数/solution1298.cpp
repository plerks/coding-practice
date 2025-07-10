/*
url: https://leetcode.cn/problems/maximum-candies-you-can-get-from-boxes/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1298 {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size(); // 盒子总数
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            auto& v = containedBoxes[i];
            for (int j : v) {
                g[i].push_back(j);
            }
        }

        int ans = 0;

        unordered_set<int> own; // 拥有的钥匙
        queue<int> q; // 放能打开的盒子
        vector<int> vis(n);
        vector<int> outside(n); // 盒子是否在外面

        auto is_open = [&](int x) { return status[x] == 1; };
        
        for (int x : initialBoxes) {
            outside[x] = true;
            if (is_open(x)) {
                q.push(x);
                vis[x] = true;
            }
        }

        while (!q.empty()) {
            int x = q.front(); q.pop();
            ans += candies[x];
            // 打开盒子发现了钥匙和盒子
            for (int y : containedBoxes[x]) {
                outside[y] = true;
            }
            // 能产生变化的是，新获得的钥匙 和 新发现的盒子
            for (int key : keys[x]) {
                if (outside[key]) {
                    if (!vis[key]) {
                        q.push(key);
                        vis[key] = true;
                    }
                }
                else own.insert(key); // 钥匙暂时不会消耗
            }
            for (int box : containedBoxes[x]) {
                if (own.count(box) || is_open(box)) {
                    if (!vis[box]) {
                        q.push(box);
                        vis[box] = true;
                    }
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1298 solu;
    /* cout << solu.maxCandies(*new vector<int>{1,0,1,0}, 
                *new vector<int>{7,5,4,100}, 
                *new vector<vector<int>>{{},{},{1},{}}, 
                *new vector<vector<int>>{{1,2},{3},{},{}},
                *new vector<int>{0}) << endl; */

    cout << solu.maxCandies(*new vector<int>{1,0,1,0}, 
                *new vector<int>{7,5,4,100}, 
                *new vector<vector<int>>{{1},{3,2},{1},{}}, 
                *new vector<vector<int>>{{1},{3},{},{2}},
                *new vector<int>{0}) << endl;
    return 0;
}
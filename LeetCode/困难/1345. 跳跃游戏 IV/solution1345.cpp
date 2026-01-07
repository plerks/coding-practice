/*
url: https://leetcode.cn/problems/jump-game-iv/
参考: https://leetcode.cn/problems/jump-game-iv/solutions/1223307/gong-shui-san-xie-noxiang-xin-ke-xue-xi-q9tb1/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1345 {
public:
    int minJumps_tle(vector<int>& arr) {
        int n = arr.size();
        if (0 == n - 1) return 0;
        unordered_map<int, vector<int>> mp; // mp[i] 表示 i 的位置
        for (int i = 0; i < n; i++) mp[arr[i]].push_back(i);

        int ans = -1;
        
        queue<int> q;
        unordered_set<int> vis;
        q.push(0);
        vis.insert(0);
        int level = 1;

        auto add = [&](int p) {
            if (!vis.count(p)) {
                if (p == n - 1) ans = level;
                q.push(p);
                vis.insert(p);
            }
        };

        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                int cur = q.front(); q.pop();
                if (cur - 1 >= 0) add(cur - 1);
                if (cur + 1 < n) add(cur + 1);
                for (int next : mp[arr[cur]]) {
                    add(next);
                }
                if (ans != -1) return ans;
            }
            level++;
        }
        return -1;
    }

    // 参考宫水三叶题解，图有 n 个节点，但是边可以有 O(n^2) 个，最坏时间复杂度会是 O(n^2) ，会超时
    // 所以，一个节点被访问过后要把它从 map 中删除，这样就可以防止访问所有边，时间复杂度 O(n)
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (0 == n - 1) return 0;
        unordered_map<int, vector<int>> mp; // mp[i] 表示 i 的位置
        for (int i = 0; i < n; i++) mp[arr[i]].push_back(i);

        int ans = -1;
        
        queue<int> q;
        vector<int> vis(n, false);
        q.push(0);
        vis[0] = true;;
        int level = 1;

        auto add = [&](int p) {
            if (!vis[p]) {
                if (p == n - 1) ans = level;
                q.push(p);
                vis[p] = true;
            }
        };

        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                int cur = q.front(); q.pop();
                if (cur - 1 >= 0) add(cur - 1);
                if (cur + 1 < n) add(cur + 1);
                auto& vec = mp[arr[cur]];
                for (int i = vec.size() - 1; i >= 0; i--) {
                    add(vec[i]);
                    vec.erase(vec.begin() + i);
                    /* 所有等值元素构成一个分量的话，第一次访问到这个分量中的某个元素后，这个分量中的所有元素都会被拉进队，
                    然后这个分量清空了，以后不会再耗时，访问这个分量只花了线性时间，即使这个分量可能有平方条边。

                    对于分量之间，每个分量最多伸出去两条边。

                    因此，总时间复杂度是线性的。
                    */
                }
                if (ans != -1) return ans;
            }
            level++;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1345 solu;
    cout << solu.minJumps(*new vector<int>{100,-23,-23,404,100,23,23,23,3,404}) << endl;
    return 0;
}
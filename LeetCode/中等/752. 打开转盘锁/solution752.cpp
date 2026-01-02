/*
url: https://leetcode.cn/problems/open-the-lock/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution752 {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> ends(deadends.begin(), deadends.end());

        auto bfs = [&]() {
            if ("0000" == target) return 0;
            queue<string> q;
            unordered_set<string> vis;
            q.push("0000");
            vis.insert("0000");
            int level = 1;
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; i++) {
                    string s = q.front(); q.pop();
                    if (ends.count(s)) continue; // s 是锁定状态，不能再动
                    for (int i = 0; i < 4; i++) { // 正向旋转
                        auto next = s;
                        next[i] = '0' + (next[i] - '0' + 1) % 10;
                        if (next == target) return level;
                        if (!vis.count(next)) { q.push(next), vis.insert(next); }
                    }
                    for (int i = 0; i < 4; i++) { // 反向旋转
                        auto next = s;
                        next[i] = '0' + (next[i] - '0' - 1 + 10) % 10;
                        if (next == target) return level;
                        if (!vis.count(next)) { q.push(next), vis.insert(next); }
                    }
                }
                level++;
            }
            return -1;
        };

        return bfs();
    }
};

int main(int argc, char const *argv[]) {
    Solution752 solu;
    cout << solu.openLock(*new vector<string>{"0201","0101","0102","1212","2002"}, "0202") << endl;
    return 0;
}
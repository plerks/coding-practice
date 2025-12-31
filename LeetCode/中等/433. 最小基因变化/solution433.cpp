/*
url: https://leetcode.cn/problems/minimum-genetic-mutation/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution433 {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        int N = 8; // startGene.length == 8
        int n = 1 + bank.size();
        bool ok = false;
        int idx = 0; // endGene的标号，排布方式为 [startGene, bank]
        for (int i = 0; i < bank.size(); i++) {
            if (bank[i] == endGene) ok = true, idx = i + 1;
        }
        if (!ok) return -1;

        vector<vector<int>> g(n);

        auto dis = [&](string& a, string& b) {
            int count = 0;
            for (int i = 0; i < N; i++) {
                if (a[i] != b[i]) count++;
            }
            return count;
        };

        vector<string> vec = bank; vec.insert(vec.begin(), startGene);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int d = dis(vec[i], vec[j]);
                if (d == 1) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }

        auto bfs = [&]() {
            queue<int> q;
            vector<int> vis(n);
            q.push(0);
            vis[0] = true;
            int level = 0;
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; i++) {
                    int node = q.front(); q.pop();
                    for (int neighbor : g[node]) {
                        if (!vis[neighbor]) {
                            if (neighbor == idx) return level + 1;
                            q.push(neighbor);
                            vis[neighbor] = true;
                        }
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
    Solution433 solu;
    cout << solu.minMutation("AACCGGTT", "AAACGGTA", *new vector<string>{"AACCGGTA","AACCGCTA","AAACGGTA"}) << endl;
    cout << solu.minMutation("AACCTTGG", "AATTCCGG", *new vector<string>{"AATTCCGG","AACCTGGG","AACCCCGG","AACCTACC"}) << endl;
    return 0;
}
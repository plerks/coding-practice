/*
url: https://leetcode.cn/problems/accounts-merge/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;

    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution721 {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> email_to_name;
        unordered_map<string, int> email_to_index;
        unordered_map<int, string> index_to_name;
        int index = 0;
        for (auto &v : accounts) {
            string& name = v[0];
            for (int i = 1; i < v.size(); i++) {
                string& email = v[i];
                if (!email_to_name.count(email)) {
                    email_to_name[email] = name;
                    email_to_index[email] = index++;
                }
            }
        }

        UnionFind uf(email_to_name.size());
        for (auto &v : accounts) {
            for (int i = 2; i < v.size(); i++) {
                uf.unite(email_to_index[v[i]], email_to_index[v[i - 1]]);
            }
        }

        map<int, vector<string>> cc; // 连通分量，(代表元编号, 连通分量的所有string)
        for (auto &[email, name] : email_to_name) {
            int index = uf.find(email_to_index[email]);
            index_to_name[index] = name;
            cc[index].push_back(email);
        }

        vector<vector<string>> ans;
        for (auto& [index, vec] : cc) {
            vector<string> temp;
            temp.push_back(index_to_name[index]);
            for (string &email : vec) temp.push_back(email);
            sort(temp.begin() + 1, temp.end());
            ans.push_back(temp);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution721 solu;
    auto a = solu.accountsMerge(*new vector<vector<string>>{
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}});
    return 0;
}
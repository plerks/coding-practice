/*
url: https://leetcode.cn/problems/find-all-possible-recipes-from-given-supplies/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2115 {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, int> string_to_index;
        int index = 0;
        for (string& s : recipes) if (!string_to_index.count(s)) if (!string_to_index.count(s)) string_to_index[s] = index++;
        for (auto& v : ingredients) for (auto &s : v) if (!string_to_index.count(s)) if (!string_to_index.count(s)) string_to_index[s] = index++;
        int n = string_to_index.size();
        vector<string> index_to_string(n);
        for (auto& [s, index] : string_to_index) index_to_string[index] = s;

        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for (int i = 0; i < recipes.size(); i++) {
            string& v = recipes[i];
            int y = string_to_index[v];
            for (auto& u : ingredients[i]) {
                int x = string_to_index[u];
                g[x].push_back(y);
                indeg[y]++;
            }
        }

        unordered_set<string> sup(supplies.begin(), supplies.end());
        unordered_set<string> rec(recipes.begin(), recipes.end());
        vector<int> ans;

        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0 && sup.count(index_to_string[i])) q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (rec.count(index_to_string[x])) ans.push_back(x);
            for (int y : g[x]) {
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);
            }
        }

        vector<string> ans2;
        for (int x : ans) {
            ans2.push_back(index_to_string[x]);
        }

        return ans2;
    }

    // 不把string转成index要方便些，直接用 unordered_map<string, vector<string>> g; 作为图，队列初始为supplies。见灵茶题解
};

int main(int argc, char const *argv[]) {
    Solution2115 solu;
    auto a = solu.findAllRecipes(*new vector<string>{"bread"}, 
                                    *new vector<vector<string>>{{"yeast","flour"}},
                                    *new vector<string>{"yeast","flour","corn"});
    return 0;
}
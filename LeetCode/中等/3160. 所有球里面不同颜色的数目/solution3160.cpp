/*
url: https://leetcode.cn/problems/find-the-number-of-distinct-colors-among-the-balls/description/
标签: LeetCode第131场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3160 {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> map; // [color, count]
        vector<int> ans;
        unordered_map<int, int> color;
        for (int i = 0; i < queries.size(); i++) {
            auto &query = queries[i];
            int x = query[0];
            int y = query[1];
            if (color.find(x) == color.end()) {
                map[y]++;
                color[x] = y;
            }
            else if (color[x] == y) {
            }
            else {
                map[y]++;
                map[color[x]]--;
                if (map[color[x]] == 0) {
                    map.erase(color[x]);
                }
                color[x] = y;
            }
            ans.push_back(map.size());
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

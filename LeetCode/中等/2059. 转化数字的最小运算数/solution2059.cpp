/*
url: https://leetcode.cn/problems/minimum-operations-to-convert-number/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2059 {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        int n = nums.size();

        queue<int> q;
        vector<int> vis(1001);
        q.push(start);
        vis[start] = true;
        int level = 0;

        auto add = [&](int x) {
            if (!(0 <= x && x <= 1000) || !vis[x]) {
                q.push(x);
                if (0 <= x && x <= 1000) vis[x] = true;
            }
        };

        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                int x = q.front(); q.pop();
                if (x == goal) return level;
                if (0 <= x && x <= 1000) {
                    for (int i = 0; i < n; i++) {
                        add(x - nums[i]);
                        add(x + nums[i]);
                        add(x ^ nums[i]);
                    }
                }
            }
            level++;
        }

        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2059 solu;
    cout << solu.minimumOperations(*new vector<int>{2,4,12}, 2, 12) << endl;
    // cout << solu.minimumOperations(*new vector<int>{3,5,7}, 0, -4) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/count-pairs-of-points-with-distance-k/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

struct Pair_hash {
    long long operator()(const pair<int, int>& p) const {
        // 0 <= xi, yi <= 10^6
        return p.first * (long long)(1e6 + 1) + p.second;
    }
};

class Solution2857 {
public:
    int countPairs_tle(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        unordered_map<pair<int, int>, int, Pair_hash> map;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = coordinates[i][0], y = coordinates[i][1];
            // 0 <= k <= 100
            for (int p = 0; p <= k; p++) { // 枚举 xx ^ x 的值，从而可以知道 yy ^ y
                int q = k - p;
                int xx = x ^ p, yy = y ^ q;
                ans += map[{xx, yy}];
            }
            map[{x, y}]++;
        }
        return ans;
    }

    // 这题有点卡常，上面的写法会超时，必须避免map的operator[]的副作用才能过
    int countPairs(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        unordered_map<pair<int, int>, int, Pair_hash> map;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = coordinates[i][0], y = coordinates[i][1];
            // 0 <= k <= 100
            for (int p = 0; p <= k; p++) { // 枚举 xx ^ x 的值，从而可以知道 yy ^ y
                int q = k - p;
                int xx = x ^ p, yy = y ^ q;
                auto it = map.find({xx, yy});
                ans += it == map.end() ? 0 : it->second;
            }
            map[{x, y}]++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2857 solu;
    cout << solu.countPairs(*new vector<vector<int>>{{1,2},{4,2},{1,3},{5,2}}, 5) << endl;
    cout << solu.countPairs(*new vector<vector<int>>{{1,3},{1,3},{1,3},{1,3},{1,3}}, 0) << endl;
    return 0;
}
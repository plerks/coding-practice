/*
url: https://leetcode.cn/problems/maximum-coins-from-k-consecutive-bags/description/
参考: https://leetcode.cn/problems/maximum-coins-from-k-consecutive-bags/solutions/3039059/hua-dong-chuang-kou-hua-liang-bian-pytho-4u47/
      https://www.bilibili.com/video/BV18srKYLEd8/
相关: LeetCode2271. 毯子覆盖的最多白色砖块数
标签: LeetCode第431场周赛
*/

// 此题前置题是LeetCode2271. 毯子覆盖的最多白色砖块数

#include <bits/stdc++.h>

using namespace std;

/* 周赛时的写法，用动态开点的线段树。
周赛时没调出来，除了要枚举端点为选取区间的右边界，还需要枚举端点为选取区间的左边界，
周赛时没多想就只枚举了选取区间的右边界在各个端点的情况。调出来后会超内存，这题区间长度是1e9的级别，coins.length也有1e5的级别，
涉及很多update，所以会超内存
*/
class Solution3413_mle {
public:
    // 区间求和 + 区间set的线段树
    unordered_map<long long, long long> tree, lazy; // 区间和，区间值

    // 查询区间和
    long long query(int L, int R, int s, int t, int p) {
        if (t < L || s > R) return 0;

        if (L <= s && t <= R) {
            return tree[p];
        }

        int m = (s + t) / 2;

        // 需要递归子问题，先将懒惰标记下压
        if (s != t && lazy.count(p)) {
            tree[2 * p] = lazy[p] * (m - s + 1);
            lazy[2 * p] = lazy[p];
            tree[2 * p + 1] = lazy[p] * (t - m);
            lazy[2 * p + 1] = lazy[p];
            lazy.erase(p);
        }

        
        return query(L, R, s, m, p * 2) + query(L, R, m + 1, t, 2 * p + 1);
    }

    // 区间set为val
    void update(int L, int R, long long val, int s, int t, int p) {
        if (t < L || s > R) return;

        if (L <= s && t <= R) {
            tree[p] = val * (t - s + 1);
            lazy[p] = val;
            return;
        }

        int m = (s + t) / 2;

        // 需要递归子问题，先将懒惰标记下压
        if (s != t && lazy.count(p)) {
            tree[2 * p] = lazy[p] * (m - s + 1);
            lazy[2 * p] = lazy[p];
            tree[2 * p + 1] = lazy[p] * (t - m);
            lazy[2 * p + 1] = lazy[p];
            lazy.erase(p);
        }

        
        update(L, R, val, s, m, p * 2);
        update(L, R, val, m + 1, t, 2 * p + 1);

        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    long long maximumCoins(vector<vector<int>>& coins, int k) {
        unordered_set<int> pos;
        for (auto& vec : coins) {
            pos.insert(vec[0]);
            pos.insert(vec[1]);
            update(vec[0], vec[1], vec[2], 0, 1e9, 1);
        }
        long long ans = 0;
        for (auto& j : pos) {
            int i = max(0, j - k + 1);
            ans = max(ans, query(i, j, 0, 1e9, 1));
        }
        for (auto& i : pos) {
            int j = max(0, i + k - 1);
            ans = max(ans, query(i, j, 0, 1e9, 1));
        }
        return ans;
    }
};

class Solution3413 {
public:
    /* 参考题解，
    与LeetCode2271. 毯子覆盖的最多白色砖块数类似，但是每个点有不同的权，这时只考虑左边界对齐或右边界对齐
    就不行了，例如 100 100 2 2，窗口大小为3，那么右边界对齐就不能获得最优解。
    为了复用LeetCode2271的代码，将coins的左边取负数反转，这样原区间的左边界对齐就变成右边界对齐，
    于是只需复用一份右边界对齐的代码
    */
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        long long ans = 0;
        sort(coins.begin(), coins.end());
        ans = maximumWhiteTiles(coins, k);

        for (auto& v : coins) {
            int t = v[0];
            v[0] = -v[1];
            v[1] = -t;
        }
        reverse(coins.begin(), coins.end());
        ans = max(ans, maximumWhiteTiles(coins, k));
        return ans;
    }

    // LeetCode2271. 毯子覆盖的最多白色砖块数 的代码做修改
    long long maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        int left = 0;
        long long cover = 0;
        long long ans = 0;
        for (auto &tile : tiles) {
            long long tl = tile[0], tr = tile[1], w = tile[2];
            cover += (tr - tl + 1) * w;
            while (tiles[left][1] < tr - carpetLen + 1) {
                cover -= (tiles[left][1] - tiles[left][0] + 1) * (long long)tiles[left][2];
                left++;
            }
            long long uncover = max((tr - carpetLen + 1 - tiles[left][0]) * (long long)tiles[left][2], 0LL);
            ans = max(ans, cover - uncover);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3413 solu;
    cout << solu.maximumCoins(*new vector<vector<int>>{{8,10,1},{1,3,2},{5,6,4}}, 4) << endl;
    return 0;
}
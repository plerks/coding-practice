/*
url: https://leetcode.cn/problems/separate-squares-ii/
参考: https://www.bilibili.com/video/BV1BRAGevERN/
      https://leetcode.cn/problems/separate-squares-ii/solutions/3078402/lazy-xian-duan-shu-sao-miao-xian-pythonj-eeqk/
      https://www.bilibili.com/video/BV1MX4y1Z7N5/
相关: LeetCode3453. 分割正方形 I, LeetCode850. 矩形面积 II
标签: LeetCode第150场双周赛, 差分, 扫描线, 矩形面积并
*/

#include <bits/stdc++.h>

using namespace std;

class SegTree {
public:
    struct Node {
        int s = 0, t = 0;
        int cnt = 0;
        int len = 0;
        int totalLen = 0;
    };

    vector<Node> tree;

    SegTree(vector<int> &xs) {
        this->n = xs.size() - 1;
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(xs, 0, n - 1, 1);
    }

    void update(int L, int R, int tag, int p) {
        if (tree[p].s > R || tree[p].t < L) return;
        int s = tree[p].s, t = tree[p].t;
        if (L <= s && t <= R) {
            tree[p].cnt += tag;
            pushup(p);
            return;
        }
        update(L, R, tag, 2 * p);
        update(L, R, tag, 2 * p + 1);
        pushup(p);
    }
private:
    int n;

    void build(vector<int> &xs, int s, int t, int p) {
        tree[p].s = s;
        tree[p].t = t;
        if (s == t) {
            tree[p].totalLen = xs[s + 1] - xs[s];
            return;
        }
        int m = (s + t) / 2;
        build(xs, s, m, 2 * p);
        build(xs, m + 1, t, 2 * p + 1);
        tree[p].totalLen = tree[2 * p].totalLen + tree[2 * p + 1].totalLen;
    }

    void pushup(int p) {
        if (tree[p].cnt) tree[p].len = tree[p].totalLen;
        else if (tree[p].s == tree[p].t) tree[p].len = 0;
        else tree[p].len = tree[2 * p].len + tree[2 * p + 1].len;
    }
};

/* 求矩形面积并的代码逻辑见`LeetCode850. 矩形面积 II`，在求矩形面积并的过程中，记录
中间过程算的面积和底边长，这样就不用跑两遍先一遍算总面积再算中间分割位置。
*/
class Solution3454 {
public:
    double separateSquares(vector<vector<int>>& squares) {
        vector<int> xs;
        struct Event { int lx, rx, y, tag; };
        vector<Event> events;
        for (auto& sq : squares) {
            int x = sq[0], y = sq[1], l = sq[2];
            xs.push_back(x);
            xs.push_back(x + l);
            events.push_back({x, x + l, y, 1});
            events.push_back({x, x + l, y + l, -1});
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        sort(events.begin(), events.end(), [](const auto &e1, const auto &e2) {
            return e1.y < e2.y;
        });

        SegTree st(xs);
        long long total = 0;
        vector<pair<long long, int>> records; // (当前总面积, 底边长)
        for (int i = 0; i < events.size() - 1; i++) {
            auto &[lx, rx, y, tag] = events[i];
            
            int l = lower_bound(xs.begin(), xs.end(), lx) - xs.begin();
            int r = lower_bound(xs.begin(), xs.end(), rx) - xs.begin();
            st.update(l, r - 1, tag, 1);
            int baseLen = st.tree[1].len;
            // 在y位置，以baseLen为底边积累面积，积累之前的累积面积为total
            records.push_back({total, baseLen});
            total = (total + (long long)baseLen * (events[i + 1].y - y));
        }
        // 最后一个面积 < 总面积/2的位置
        int index = lower_bound(records.begin(), records.end(), total, [](const auto&x, const long long total) {
            return x.first * 2LL < total;
        }) - records.begin() - 1;
        int y = events[index].y;
        long long area = records[index].first;
        int baseLen = records[index].second;
        return y + (total / 2.0 - area) / baseLen;
    }
};

int main(int argc, char const *argv[]) {
    Solution3454 solu;
    cout << solu.separateSquares(*new vector<vector<int>>{{0,0,1},{2,2,1}}) << endl;
    cout << solu.separateSquares(*new vector<vector<int>>{{0,0,2},{1,1,1}}) << endl;
    return 0;
}
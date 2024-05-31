/*
url: https://leetcode.cn/problems/block-placement-queries/description/
参考: https://leetcode.cn/problems/block-placement-queries/solutions/2790395/ping-heng-shu-xian-duan-shu-pythonjavacg-8klz/
      https://www.bilibili.com/video/BV1SU411d7wj/
相关: LeetCode2334. 元素值大于变化阈值的子数组
标签: LeetCode第131场双周赛, 线段树, 反向, 树状数组, 特殊树状数组, 并查集, 并查集的奇妙用法
*/

// 这次周赛做出前3题

#include <bits/stdc++.h>

using namespace std;

// 区间set + 区间求max的线段树，用`典型问题/线段树/区间set + 区间求max`改了下
class SegTree {
private:
    vector<int> tree, lazy;
    int n;
    
    void pushup(int p) {
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    void modify(int L, int R, int val, int s, int t, int p) {
        if (L <= s && t <= R) {
            tree[p] = val;
            lazy[p] = val;
            return;
        }
        pushdown(s, t, p);
        int m = s + ((t - s) >> 1);
        if (L <= m) modify(L, R, val, s, m, p * 2);
        if (R > m) modify(L, R, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    void pushdown(int s, int t, int p) {
        if (s != t && lazy[p] > 0) { // 这里要求set时提供的val > 0，因为要用lazy[p]的值是否>0来区分是否有懒惰标记
            tree[p * 2] = tree[p];
            lazy[p * 2] = lazy[p];
            tree[p * 2 + 1] = tree[p];
            lazy[p * 2 + 1] = lazy[p];
            lazy[p] = 0;
        }
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) {
            return tree[p];
        }
        int m = s + ((t - s) >> 1);
        int mx = 0;
        if (L <= m) mx = max(mx, query(L, R, s, m, p * 2));
        if (R > m) mx = max(mx, query(L, R, m + 1, t, p * 2 + 1));
        return mx;
    }

public:
    SegTree(int n) {
        this->n = n;
        tree.resize(2 << (32 - __builtin_clz(n)));
        lazy.resize(2 << (32 - __builtin_clz(n)));
        // 不用build什么，初始全是0
    }

    void modify(int L, int R, int val) { modify(L, R, val, 0, n - 1, 1); }

    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }
};

// 单点set + 区间求max的线段树，用`典型问题/线段树/单点set + 区间求max`改了下
class SegTreePointSetRangeMax {
private:
    vector<int> tree; // 单点修改，只会在叶节点上修改，无需懒惰标记
    int n;
    
    void pushup(int p) {
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    void modify(int I, int val, int s, int t, int p) { // I为要修改值的位置
        if (s == t) {
            tree[p] = val;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (I <= m) modify(I, val, s, m, p * 2);
        if (I > m) modify(I, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    int query(int L, int R, int s, int t, int p) {
        if (L <= s && t <= R) {
            return tree[p];
        }
        int m = s + ((t - s) >> 1);
        int mx = 0;
        if (L <= m) mx = max(mx, query(L, R, s, m, p * 2));
        if (R > m) mx = max(mx, query(L, R, m + 1, t, p * 2 + 1));
        return mx;
    }

public:
    SegTreePointSetRangeMax(int n) {
        this->n = n;
        tree.resize(2 << (32 - __builtin_clz(n)));
    }

    void modify(int I, int val) { modify(I, val, 0, n - 1, 1); }

    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }
};

// 在set只会将值增大的情况下，可以有单点set + 前缀求max的树状数组
class SpecialFenwick {
    vector<int> nums;
    vector<int> tree;

public:
    // 初始全为0
    SpecialFenwick(int n) : nums(n), tree(n + 1) {
    }

    void modify(int index, int val) {
        int mx = max(tree[index + 1], val);
        for (int i = index + 1; i < tree.size(); i += i & -i) {
            tree[i] = max(tree[i], mx);
        }
    }

    // 求nums[0, index]的max
    int query(int index) {
        int mx = INT_MIN;
        for (int i = index + 1; i > 0; i &= i - 1) { // i -= lowbit(i)等价于i &= i - 1
            mx = max(mx, tree[i]);
        }
        return mx;
    }
};

class UnionFind {
public:
    vector<int> parent;

    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
};

class Solution3161 {
public:
    // 周赛时写的暴力解法，737 / 742 个通过的测试用例，超时，对操作1能二分查找到相应的区间并一分为二，对操作2就不行了，只能顺序遍历
    vector<bool> getResults_time_limit_exceeded(vector<vector<int>>& queries) {
        map<int, int> map;
        map[0] = 6 * 1e4;
        vector<bool> ans;
        for (auto &query : queries) {
            int type = query[0];
            if (type == 1) {
                int x = query[1];
                auto it = map.upper_bound(x);
                if (it != map.begin()) it--;
                int left = it->first;
                int right = it->second;
                map.erase(it);
                map.insert(make_pair(left, x));
                map.insert(make_pair(x, right));
            }
            else {
                int x = query[1];
                int sz = query[2];
                bool success = false;
                for (auto it = map.begin(); it != map.end() && it->first <= x; it++) {
                    int left = it->first;
                    int right = it->second;
                    if (min(x, right) - left >= sz) {
                        ans.push_back(true);
                        success = true;
                        break;
                    }
                }
                if (!success) ans.push_back(false);
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法一，用区间set + 区间求max的线段树
    vector<bool> getResults(vector<vector<int>>& queries) {
        /* 把区间长度记录在右端点上，这样查询<=x部分的最长区间，只需求tree[0...x]的
        最大值，再算上最后可能有的一截。如果记在左端点上，就有其对应的右端点可能>x的问题
        */
        int n = 0;
        for (auto &q : queries) {
            n = max(n, q[1]);
        }
        // 放障碍物的下标最大为n，则要线段树化的数组最多有n + 1个元素
        SegTree segTree(n + 1); // 这里如果写成n，一开始的线段树节点p代表的nums范围就不对，但是能过挺多用例，742 / 744 个通过的测试用例，对{{1,11},{1,1},{1,12},{2,1,6},{2,11,4}}这个用例会出错
        set<int> set = {0};
        vector<bool> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int x = q[1];
                auto it = set.upper_bound(x);
                if (it != set.end()) {
                    segTree.modify(*it, *it, *it - x);
                }
                int prev = *(--it); // x一定有前一个元素，这里无需担心越界，因为x >= 1，有0在前面兜底
                // 这题数据保证当操作执行的时候，位置x处没有任何障碍物，且x >= 1，所以x - prev不会是0，所以lazy[p]不会被赋值为0，可以用lazy[p]是否大于0来判断是否有懒惰标记
                segTree.modify(x, x, x - prev);
                set.insert(x);
            }
            else {
                int x = q[1];
                int sz = q[2];
                int near = *(--set.upper_bound(x)); // <=x 位置最近的障碍
                int mx = max(segTree.query(0, near), x - near);
                if (mx >= sz) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法一，用单点修改的线段树
    vector<bool> getResults_implementation2(vector<vector<int>>& queries) {
        int n = 0;
        for (auto &q : queries) {
            n = max(n, q[1]);
        }
        // 放障碍物的下标最大为n，则要线段树化的数组最多有n + 1个元素
        SegTreePointSetRangeMax segTree(n + 1);
        set<int> set = {0};
        vector<bool> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int x = q[1];
                auto it = set.upper_bound(x);
                if (it != set.end()) {
                    segTree.modify(*it, *it - x);
                }
                int prev = *(--it); // x一定有前一个元素，这里无需担心越界，因为x >= 1，有0在前面兜底
                // 这题数据保证当操作执行的时候，位置x处没有任何障碍物，且x >= 1，所以x - prev不会是0，所以lazy[p]不会被赋值为0，可以用lazy[p]是否大于0来判断是否有懒惰标记
                segTree.modify(x, x - prev);
                set.insert(x);
            }
            else {
                int x = q[1];
                int sz = q[2];
                int near = *(--set.upper_bound(x)); // <=x 位置最近的障碍
                int mx = max(segTree.query(0, near), x - near);
                if (mx >= sz) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二，很巧妙，倒序回答询问，这样增加障碍物就变成了移除障碍物，这样数组的值一定是增大，单点set只会set大的情况下，
    可以有单点set + 前缀求max的树状数组。注意本来树状数组不适合单点set + 前缀求max的场景，因为set之后有可能把关键区间的最大值set没了，
    需要遍历一遍才能知道现在关键区间的最大值，这样时间复杂度就O(n)了。 */
    vector<bool> getResults_implementation3(vector<vector<int>>& queries) {
        int n = 0;
        vector<int> obstacles = {0};
        for (auto &q : queries) {
            n = max(n, q[1]);
            if (q[0] == 1) obstacles.push_back(q[1]);
        }
        sort(obstacles.begin(), obstacles.end());
        set<int> set(obstacles.begin(), obstacles.end());
        SpecialFenwick sf(n + 1); // 障碍物最大下标为n, 元素个数是n + 1
        for (int i = 1; i < obstacles.size(); i++) {
            sf.modify(obstacles[i], obstacles[i] - obstacles[i - 1]);
        }
        vector<bool> ans;
        for (int i = queries.size() - 1; i >= 0; i--) {
            auto &q = queries[i];
            int type = q[0];
            if (type == 1) {
                int x = q[1]; // 倒序回答询问，现在是把x位置的障碍物拿起来
                auto it = set.lower_bound(x); // it一定是x
                auto next = std::next(it);
                auto prev = std::prev(it); // 一定有prev，因为x>=1且set里放了个0
                if (next != set.end()) {
                    sf.modify(*next, *next - *prev);
                }
                set.erase(it);
            }
            else {
                int x = q[1];
                int sz = q[2];
                auto it = --set.upper_bound(x);
                int near = *it; // <=x位置的第一个障碍物位置
                if (max(sf.query(near), x - near) >= sz) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    /* 灵茶山艾府题解解法三，倒序回答询问 + 并查集的奇妙用法。用两个并查集实现上一种方法中用set找前后最近障碍物的功能。
    具体来说，两个并查集left, right，分别用来求一个障碍物左侧和右侧最近的障碍物位置。以left为例，遍历初始化left的每个
    位置时，若是障碍物则直接指向自己，若不是障碍物则直接指向上一个障碍物。查找<x位置的第一个障碍物时，直接找x-1位置的代表元，
    查找<=x位置的第一个障碍物时，直接找x位置的代表元。
    也就是，把非障碍物位置合并到左右第一个障碍物位置里，障碍物位置合并到自己。或者说，往隔板聚拢。

    LeetCode2334. 元素值大于变化阈值的子数组中也以特殊的方式使用了并查集。
    */
    vector<bool> getResults_implementation4(vector<vector<int>>& queries) {
        int n = 0;
        vector<int> obstacles = {0};
        for (auto &q : queries) {
            n = max(n, q[1]);
            if (q[0] == 1) obstacles.push_back(q[1]);
        }
        sort(obstacles.begin(), obstacles.end());
        UnionFind left(n + 2);
        UnionFind right(n + 2);
        SpecialFenwick sf(n + 2); // 障碍物最大下标为n, 元素个数是n + 1，再算上最后加个哨兵隔板
        for (int i = 1; i < obstacles.size(); i++) {
            int p = obstacles[i - 1];
            int q = obstacles[i];
            sf.modify(q, q - p);
            for (int j = p + 1; j < q; j++) { // 中间非障碍物的节点分别指向左边和右边最近的障碍物
                left.parent[j] = p;
                right.parent[j] = q;
            }
        }
        // n + 1位置插块板子作为哨兵，然后把最后一块真实隔板到最后一块哨兵隔板中间的部分指一下
        for (int j = obstacles.back() + 1; j < n + 2; j++) {
            left.parent[j] = obstacles.back();
            right.parent[j] = n + 1;
        }
        vector<bool> ans;
        for (int i = queries.size() - 1; i >= 0; i--) {
            auto &q = queries[i];
            int type = q[0];
            if (type == 1) {
                int x = q[1]; // 倒序回答询问，现在是把x位置的障碍物拿起来
                int prev = left.find(x - 1); // left.find(x - 1)是<x的第一个障碍物
                int next = right.find(x + 1);
                sf.modify(next, next - prev);
                left.parent[x] = prev; // 拿起x处的隔板
                right.parent[x] = next; // 拿起x处的隔板
                // 拿起x处的隔板也可以写成，并查集，后面find时会路径压缩，效果是一样的
                /* left.parent[x] = x - 1;
                right.parent[x] = x + 1; */
            }
            else {
                int x = q[1];
                int sz = q[2];
                int near = left.find(x); // <=x位置的第一个障碍物位置
                if (max(sf.query(near), x - near) >= sz) {
                    ans.push_back(true);
                }
                else ans.push_back(false);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3161 solu;
    vector<vector<int>> v = {{1,11},{1,1},{1,12},{2,1,6},{2,11,4}};
    auto a = solu.getResults(v);
    auto b = solu.getResults_implementation2(v);
    auto c = solu.getResults_implementation3(v);
    auto d = solu.getResults_implementation4(v);
    return 0;
}

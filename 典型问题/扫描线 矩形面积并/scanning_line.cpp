/*
描述: 对给出的平面上一些矩形(x1, y1, x2, y2)，(x1, y1)和(x2, y2)分别代表矩形左上和右下点的坐标，求出这些矩形的面积并(重叠部分只算一次)
数据范围: 矩形的个数在1e5级别，但是坐标在1e9级别
参考: https://leetcode.cn/problems/rectangle-area-ii/solutions/3078272/lazy-xian-duan-shu-sao-miao-xian-pythonj-4tkr/
      https://www.bilibili.com/video/BV1MX4y1Z7N5/
      https://leetcode.cn/problems/rectangle-area-ii/solutions/1825859/ju-xing-mian-ji-ii-by-leetcode-solution-ulqz/
相关: LeetCode850. 矩形面积 II, LeetCode3454. 分割正方形 II
时间复杂度: O(nlogn)，n为矩形个数
*/

#include <bits/stdc++.h>

using namespace std;

/* 线段树功能：对于一个数组nums初始全为0(初始覆盖次数为0)，会对数组区间做区间+1/-1操作，且保证不会减到负数，每个点有个权值(长度)，
线段树要给出nums中所有>0的点的权值之和。
<https://www.bilibili.com/video/BV1MX4y1Z7N5/>中的写法：
*/
class SegTree {
public:
    struct Node {
        int s = 0, t = 0; // 节点管辖区间范围，也可以像普通的写法一样在参数里和p一样带着走
        /* 区间被完整覆盖的次数。注意这里很关键，当更新只涉及这个节点的一部分时是不修改cnt的，
        而是继续递归下去，只有当要修改区间完全包含当前节点时才修改cnt。这样就规避了一个区间中
        的各个点的累积覆盖次数可能不同的问题。
        */
        int cnt = 0;
        int len = 0; // 区间覆盖长度
        int totalLen = 0; // 区间总长
    };

    vector<Node> tree;

    SegTree(vector<int> &xs) {
        this->n = xs.size() - 1; // 有xs.size()-1个区间，每个区间为一个"线段树维护的区间中的点"，用线段树维护这些"点"
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(xs, 0, n - 1, 1);
    }

    /* 这里cnt起到了类似懒惰标记的作用，而且甚至没有把懒惰标记向下传的操作！非常特别
    为什么不需要懒惰标记下传？
    例如[0, 1]分为[0], [1]，当[0, 1]的完整覆盖次数-1时，为什么不用把[0]，[1]的覆盖次数也-1？
    因为之前[0, 1]的完整覆盖次数+1时，也没有下传到[0]，[1]。
    上面的节点的cnt>0时，不用看下面的节点，当上面的节点cnt==0时，这里的信息又对下面没影响。
    */
    void update(int L, int R, int tag, int p) { // [L, R]增加覆盖，次数为tag(+1/-1)
        if (tree[p].s > R || tree[p].t < L) return;
        int s = tree[p].s, t = tree[p].t;
        if (L <= s && t <= R) {
            tree[p].cnt += tag;
            pushup(p); // p处也要pushup一次，这里特别
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
        /* update()，一直递归向下到达完全被更新区间包含的节点(懒惰节点)，然后更新节点的cnt，
        注意cnt是这个节点被完整覆盖的次数，
        若cnt > 0，则说明当前节点被完全覆盖，则覆盖长度为totalLen；
        若cnt == 0 (注意cnt不会<0，一次完全覆盖的离开，在前面一定有一次完整覆盖的进入)，不能说明当前节点的覆盖
        长度为0，可能子节点有部分覆盖的长度，所以要用子节点的覆盖长度相加：tree[2 * p].len + tree[2 * p + 1].len，
        但是如果叶节点的完整覆盖次数为0，则覆盖长度就是0了，所以还要对叶节点特判，不然叶节点的cnt为0时，它会去找外部节点
        来算自己的len，这会导致越界。

        为什么需要`if (tree[p].cnt) tree[p].len = tree[p].totalLen;`，为什么不直接就用两个子节点的len相加来算自己的len？
        因为若当前节点的cnt>0，这时候用子节点的len相加反而是可能偏小的，比如p之前被部分覆盖，然后现在被完整覆盖，则覆盖长度
        应该为全长而非部分长。
        也就是说，只有当p发生脱离覆盖以至于完全覆盖次数为0时，才能用儿子的len来算，这时儿子才表现出来。很特别！

        p的len确定之后，再往上的pushup也是类似的逻辑。
        */
        if (tree[p].cnt) tree[p].len = tree[p].totalLen;
        else if (tree[p].s == tree[p].t) tree[p].len = 0;
        else tree[p].len = tree[2 * p].len + tree[2 * p + 1].len;
    }
};

class ScanningLine {
public:
    /* 参考讲解，
    一条自下而上的水平的扫描线去扫描多个矩形取并后构成的图形，这条扫描线与图形有多段交线段，重要的是求出这些交线的和，
    这个和就是这段扫描内，面积增加的底边长之和。
    扫描线不需要每次只增加1地向上移动，由于只有在矩形边界上才会发生变化，因此只需考虑所有的矩形上下边界即可(记作events)。
    矩形数目 << y坐标范围(1e9)，因此能显著减小扫描次数。
    现在的问题是：如何求扫描线在某一个位置的底边长之和，将矩形按左右边界纵切，这样就切出了互不相交的多个纵向无限长的长纸条，
    以`./BV1MX4y1Z7N5的讲解图.jpg`为例，这里的纵条指的是[10,20],[20,30],[30,50],[50,80],[80,90]，纵向视作无限长。
    遍历events(枚举扫描线)，遍历events的过程中，如果是下边界则为入，上边界则为出，把所有在y = events[i]处的边界线用完，
    根据入和出计算每条纸条的位置是否有矩形(由于纸条已经极窄化，要么矩形完全覆盖这个纸条，要么完全不覆盖，不存在部分覆盖的情况)，
    并且，由于矩形可以重叠，所以要记录重叠次数，才能确定出入后，这个纸条是否是要贡献面积的。
    这样有两层循环，遍历events和遍历纸条，时间复杂度为O(n^2)，还可以优化。
    例如，在y=1处，进入了[20, 80]这条边，这使得[20,30],[30,50],[50,80]在下一次event之前是有矩形的，所以此时底边长为60，
    区间的分解和维护提醒我们用线段树来计算有矩形的纸条的长度之和。
    
    当在y位置有条[lx, rx]范围的线段入时，其包含的所有纸条的覆盖次数都要增加一次，若是线段出则减少一次；根据这些差分线
    可以知道当前在这些基纸条上的重叠次数，更新线段树，从线段树得到当前y处积累的底边长即可计算到下一条扫描线之间的面积。
    如果坐标范围小的话，对坐标范围用线段树就行，但是这题坐标范围大(1e9)，所以得对纸条的编号用线段树。
    想要求的是整个区间的有覆盖长度，更新操作的逻辑是把某个区间的覆盖数+1/-1，
    */
    int rectangleArea(vector<vector<int>>& rectangles) {
        const int MOD = 1e9 + 7;
        vector<int> xs; // 各个横坐标分界线
        struct Event { int lx, rx, y, tag; }; // 矩形上下边界线段的左右横坐标，y坐标，性质(+1代表是下边界入边，-1代表是上边界出边)
        vector<Event> events;
        for (auto& rect : rectangles) {
            xs.push_back(rect[0]);
            xs.push_back(rect[2]);
            events.push_back({rect[0], rect[2], rect[1], 1});
            events.push_back({rect[0], rect[2], rect[3], -1});
        }
        // 排序去重
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        sort(events.begin(), events.end(), [](const auto &e1, const auto &e2) {
            return e1.y < e2.y;
        });

        /* xs为离散化后的x坐标，[xs[i], xs[i + 1])才是一段区间，线段树要维护每个区间的有重叠长度，
        且线段树的叶子节点是这n-1个区间，后续更新时要修改的区间也一定是这n-1个基区间组合起来的，不存在只更新基区间的一部分的情况。
        注意，这很重要！这些基区间是不可拆分的，线段树中的每个叶子代表一个基区间！这样就是普通的线段树了
        */
        SegTree st(xs);
        long long ans = 0;
        for (int i = 0; i < events.size() - 1; i++) {
            auto &[lx, rx, y, tag] = events[i];
            // [lx, rx]中的基区间要增加覆盖次数tag
            int l = lower_bound(xs.begin(), xs.end(), lx) - xs.begin(); // lx的位置，xs无重复且一定有==lx的位置。这里似乎可以预处理xs，得到[值, 下标]的map，不用二分
            int r = lower_bound(xs.begin(), xs.end(), rx) - xs.begin(); // rx的位置
            st.update(l, r - 1, tag, 1); // xs[l, r]这几条竖线对应的区间编号范围为[l, r - 1]
            // 底边长，虽然events可能有多个y相同的元素，但是只有到变化的位置events[i + 1].y - y才不为0，这时baseLen已经是y处的底边总长了
            int baseLen = st.tree[1].len;
            ans = (ans + (long long)baseLen * (events[i + 1].y - y)) % MOD;
        }
        return ans;
    }
};

/* 线段树功能：对于一个数组nums初始全为0(初始覆盖次数为0)，会对数组区间做区间+1/-1操作，且保证不会减到负数，每个点有个权值(长度)，
线段树要给出nums中所有>0的点的权值之和。
灵茶题解中的写法：
直接来想这个问题，要计算一个区间的有覆盖长度，覆盖次数>0的地方都是有覆盖，覆盖次数==0的地方是无覆盖，
于是考虑维护覆盖次数==0的长度，假设一个区间长为5，覆盖次数为1 1 2 2 2，那么区间减少一次覆盖后，无覆盖
长度为多少？无法得知，所以要把 维护覆盖次数==0的长度 变成 维护覆盖次数最小的长度，如果min_cover_cnt == 0，
那么就可以通过min_cover_len知道无覆盖长度，如果min_cover_cnt > 0，那么整个区间就都是有覆盖的
*/
class SegTree_implementation2 {
public:
    struct Node {
        int s = 0, t = 0;
        int min_cover_len = 0; // 区间内取最小覆盖次数的长度
        int min_cover_cnt = 0; // 区间内的最小覆盖次数
        int lazy = 0;
    };

    vector<Node> tree;

    SegTree_implementation2(vector<int> &xs) {
        this->n = xs.size() - 1;
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(xs, 0, n - 1, 1);
    }

    void update(int L, int R, int tag, int p) { // [L, R]增加覆盖，次数为tag(+1/-1)
        if (tree[p].s > R || tree[p].t < L) return;
        int s = tree[p].s, t = tree[p].t;
        if (L <= s && t <= R) {
            tree[p].min_cover_cnt += tag; // 区间都受到了tag影响，min_cover_len这个长度不会变
            tree[p].lazy += tag;
            return;
        }

        // 需要递归子节点，懒惰标记下推
        tree[2 * p].min_cover_cnt += tree[p].lazy;
        tree[2 * p + 1].min_cover_cnt += tree[p].lazy;
        tree[2 * p].lazy += tree[p].lazy;
        tree[2 * p + 1].lazy += tree[p].lazy;
        tree[p].lazy = 0;

        update(L, R, tag, 2 * p);
        update(L, R, tag, 2 * p + 1);
        pushup(p);
    }

    // 返回覆盖次数为0的长度，这要看最小覆盖次数是否为0
    int get_uncovered_len() {
        return tree[1].min_cover_cnt == 0 ? tree[1].min_cover_len : 0;
    }
private:
    int n;

    void build(vector<int> &xs, int s, int t, int p) {
        tree[p].s = s;
        tree[p].t = t;
        if (s == t) {
            tree[p].min_cover_len = xs[s + 1] - xs[s];
            return;
        }
        int m = (s + t) / 2;
        build(xs, s, m, 2 * p);
        build(xs, m + 1, t, 2 * p + 1);
        tree[p].min_cover_len = tree[2 * p].min_cover_len + tree[2 * p + 1].min_cover_len;
    }

    void pushup(int p) {
        tree[p].min_cover_cnt = min(tree[2 * p].min_cover_cnt, tree[2 * p + 1].min_cover_cnt);
        tree[p].min_cover_len = (tree[2 * p].min_cover_cnt == tree[p].min_cover_cnt ? tree[2 * p].min_cover_len : 0)
                                + (tree[2 * p + 1].min_cover_cnt == tree[p].min_cover_cnt ? tree[2 * p + 1].min_cover_len : 0);
    }
};

class ScanningLine_implementation2 {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        const int MOD = 1e9 + 7;
        vector<int> xs; // 各个横坐标分界线
        struct Event { int lx, rx, y, tag; }; // 矩形上下边界线段的左右横坐标，y坐标，性质(+1代表是下边界入边，-1代表是上边界出边)
        vector<Event> events;
        for (auto& rect : rectangles) {
            xs.push_back(rect[0]);
            xs.push_back(rect[2]);
            events.push_back({rect[0], rect[2], rect[1], 1});
            events.push_back({rect[0], rect[2], rect[3], -1});
        }
        // 排序去重
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        sort(events.begin(), events.end(), [](const auto &e1, const auto &e2) {
            return e1.y < e2.y;
        });

        /* xs为离散化后的x坐标，[xs[i], xs[i + 1])才是一段区间，线段树要维护每个区间的有重叠长度，
        且线段树的叶子节点是这n-1个区间，后续更新时要修改的区间也一定是这n-1个基区间组合起来的，不存在只更新基区间的一部分的情况。
        注意，这很重要！这些基区间是不可拆分的，线段树中的每个叶子代表一个基区间！这样就是普通的线段树了
        */
        SegTree_implementation2 st(xs);
        long long ans = 0;
        for (int i = 0; i < events.size() - 1; i++) {
            auto &[lx, rx, y, tag] = events[i];
            // [lx, rx]中的基区间要增加覆盖次数tag
            int l = lower_bound(xs.begin(), xs.end(), lx) - xs.begin(); // lx的位置，xs无重复且一定有==lx的位置。这里似乎可以预处理xs，得到[值, 下标]的map，不用二分
            int r = lower_bound(xs.begin(), xs.end(), rx) - xs.begin(); // rx的位置
            st.update(l, r - 1, tag, 1); // xs[l, r]这几条竖线对应的区间编号范围为[l, r - 1]
            // 底边长，虽然events可能有多个y相同的元素，但是只有到变化的位置events[i + 1].y - y才不为0，这时baseLen已经是y处的底边总长了
            int baseLen = xs.back() - xs[0] - st.get_uncovered_len();
            ans = (ans + (long long)baseLen * (events[i + 1].y - y)) % MOD;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    ScanningLine solu;
    cout << solu.rectangleArea(*new vector<vector<int>>{{0,0,2,2},{1,0,2,3},{1,0,3,1}}) << endl;

    ScanningLine_implementation2 solu2;
    cout << solu2.rectangleArea(*new vector<vector<int>>{{0,0,2,2},{1,0,2,3},{1,0,3,1}}) << endl;
    return 0;
}
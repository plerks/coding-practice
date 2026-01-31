/*
url: https://www.luogu.com.cn/problem/P1972
参考: https://www.luogu.com.cn/article/j7n2fv29
标签: 离线, 扫描线, 线段树, 差分
*/

/* 另外一种思路，对于 [l, r] 区间内的值，我们有数次值 x 的出现，但是对于“统计元素种数”只会计数一次，如何考虑这个“一次”？
观察到这件事：这些 x 都出现在 [l, r] 内，这样想没特别的。但是，只有第一个 x ，其 “上一次 x 的出现位置” <= l - 1。

记 pre_i 为 nums[i] 这个值上一次出现的位置，可以用 [l, r] 中 pre_i <= l - 1 这个事件的发生次数来统计 [l, r] 中的元素种数，如果没出现就是 0。

将 i 作为横坐标，pre_i 作为纵坐标，将 (i, pre_i) 放在平面中。则区间 [l, r] 的答案为 以(l, 0)为左下角，以(r, l - 1)为右上角的矩形(包含边界)
内有多少个点，这就将问题转换为了简单的数点计数问题。

这个数点问题是可以用前缀和差分的，把 {左下角(l, 0)，右上角(r, l - 1)的数点} 转换为 {左下角(0, 0)，右上角(r, l - 1)} - {左下角(0, 0)，右上角(l - 1, r - 1)}。
注意原本的问题是不能用前缀和作差的，nums = {1, 2, 2}，[2, 2]的元素种数 != [0, 2]的元素种数 - [0, 1]的元素种数，但是转换为单纯的计数问题后，
可以用前缀和作差了。

对于一个前缀矩形(右上角(x, y))的数点，
1. 如何保证横坐标 <= x？考虑差分（或者应该叫考虑离散点？），将所有横坐标排序，然后从左到右，边维护边计算
2. 如何保证纵坐标 <= y？用线段树来求 [0, y] 的点的个数，线段树里存的是 y 坐标值的出现次数

还有一个关键问题，当我们要计算区间[l, r]的答案时，我们是不能直接把 pre[l, r] 的值放进线段树的，因为下一个区间的 r' 可能更小，但是不合适的横坐标的点对应
的纵坐标却已经放进去不好删掉了。或者这样理解：[l, r] 的两个边界是两个状态，不能直接操作。
所以要用扫描线，用扫描线从左往右扫，对每个离散横坐标，其位置处有 nums元素 / query的l, r ，记录好type，在那个横坐标位置进行维护。
比如，对一个查询 [l, r] ，我们要在扫到 l - 1 时把 - {以 (l - 1, r - 1) 为右上角的前缀矩形点数} 加到这个 query 的 ans 里，
扫到 r 时把 {以 (r, l - 1) 为右上角的前缀矩形点数} 加到这个 query 的 ans 里。把这些要做的操作先记录好。

这个有点像刷表法？就是扫描线去看自己该更新哪些 query，那些 query 区间已经先登记好了扫描线到左右位置的时候计算下前缀矩形点数。

线段树记录的是当前扫描线左侧，纵坐标在 y 位置的点数
*/

#include <bits/stdc++.h>

using namespace std;

int rd() {
    int k = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    return f ? k : -k;
}
void wr(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}

const int maxn = 1e6 + 1;

// 操作
struct Op {
    int type; // 0 代表加点，1 代表加，2 代表减。由于矩形包含边界，要先加点再计算 query
    int x, y; // (x, y) 代表前缀矩形的右上角
    int id;
};

bool cmp(const Op& a, const Op& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.type < b.type;
}

struct Query {
    int l, r, id;
};

int n, m;

Op op[3 * maxn]; int total; // 每个 nums[i] 一个 op，每个 query 两个 op，最多 3 * maxn

int nums[maxn + 1]; // nums从 1 开始放元素
int pre[maxn + 1]; // pre[i] 表示 nums[i] 在 nums 中上一次出现的位置，0 表示未出现
int pos[maxn]; // pos[x] 表示 x 的最近出现位置
Query queries[maxn];

int tree[4 * maxn];

void modify(int index, int diff, int s, int t, int p) {
    if (s == t) {
        tree[p] += diff;
        return;
    }
    int m = s + (t - s) / 2;
    if (index <= m) modify(index, diff, s, m, 2 * p);
    else modify(index, diff, m + 1, t, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int L, int R, int s, int t, int p) {
    if (L <= s && t <= R) return tree[p];
    int m = s + (t - s) / 2;
    int sum = 0;
    if (L <= m) sum += query(L, R, s, m, 2 * p);
    if (R > m) sum += query(L, R, m + 1, t, 2 * p + 1);
    return sum;
}

int ans[maxn];

signed main(int argc, char const *argv[]) {
    n = rd();
    for (int i = 1; i <= n; i++) {
        nums[i] = rd();
        pre[i] = pos[nums[i]];
        pos[nums[i]] = i;
        op[total++] = {0, i, pre[i], -1};
    }
    m = rd();
    for (int i = 1; i <= m; i++) {
        int l = rd(), r = rd(); // 编号从 1 开始，l - 1, r - 1 不会出现负数
        queries[i] = {l, r, i - 1};
        op[total++] = {2, l - 1, r - 1, i - 1};
        op[total++] = {1, r, l - 1, i - 1};
    }
    sort(op, op + total, cmp);
    for (int i = 0; i < total; i++) {
        auto [type, x, y, id] = op[i]; // x 是当前扫描线所在位置，相当于扫描线在扫有值的那些横坐标点（也可理解成在扫 op 的下标）
        if (type == 0) {
            modify(y, 1, 0, n, 1);
        }
        else if (type == 1) {
            ans[id] += query(0, y, 0, n, 1);
        }
        else ans[id] -= query(0, y, 0, n, 1);
    }
    for (int i = 0; i < m; i++) {
        wr(ans[i]); putchar('\n');
    }
    return 0;
}
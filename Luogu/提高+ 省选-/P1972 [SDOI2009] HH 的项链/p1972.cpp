/*
url: https://www.luogu.com.cn/problem/P1972
参考: https://www.luogu.com.cn/article/boho8rhn
相关: 洛谷P4113. 采花, smqyojP435
标签: 离线, 贡献, 树状数组
*/

// 这题数据是 1e6 级别，用莫队会超时

/* 思路:
多个重复元素对于"统计不同元素的个数"只有一次贡献，将这次贡献视为最右边的那个 x 贡献的，以 mp[i] = 1 表示 i 是最靠右的 nums[i] 值所在
于是我们将查询按 r 排序，当我们遇到一个新的 [l, r] 查询时，将nums中所有没加入的位置加入进去，然后现在 mp 中的 1 是所有最靠右的独特值所在位置，
则对于一个查询 [l, r]，1 会尽全力记在 [l, r] 中，只需用树状数组记录 map[l, r] 的 sum 就是元素种数了。

总结一下：用树状数组记录最靠右的“贡献元素”在 nums 中的位置，将那个位置在树状数组中写成 1
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

int n, m;
const int maxn = 1e6 + 1;
int nums[maxn];

struct Query {
    int l, r, id;
};

Query queries[maxn];

int tree[maxn + 1]; // tree[i + 1] = 1 表示 i 是当前的 [0, r] 的最靠右 nums[i] 值所在位置

int lowbit(int x) { return x & -x; }

void modify(int index, int diff) {
    for (int i = index + 1; i < n + 1; i = i + lowbit(i)) {
        tree[i] += diff;
    }
}

int pre_sum(int R) {
    R++;
    int sum = 0;
    while (R > 0) {
        sum += tree[R];
        R -= lowbit(R);
    }
    return sum;
}

// 区间求和
int query(int L, int R) {
    return pre_sum(R) - pre_sum(L - 1);
}

bool cmp(const Query& x, const Query& y) {
    return x.r < y.r;
}

int pos[maxn]; // pos[x] 表示 x 这个值的出现当前被记录在 nums[pos[x]] 位置上

auto init = []() {
    memset(pos, -1, sizeof(int) * maxn);
    return 0;
}();


int main(int argc, char const *argv[]) {
    n = rd();
    for (int i = 0; i < n; i++) nums[i] = rd();
    m = rd();
    for (int i = 0; i < m; i++) {
        queries[i] = {rd() - 1, rd() - 1, i};
    }
    sort(queries, queries + m, cmp);
    vector<int> ans(m);
    int p = 0; // nums[0, p) 的点已经加入树状数组中，树状数组记录贡献元素在nums中的位置，用 1 表示这个位置是贡献元素
    for (int i = 0; i < m; i++) { // 枚举 queries，可以看做扫描线在扫 queries 的下标(或者说 queries 的 r)，归根结底都是在扫 nums 的下标，而 query 根据自己的 r 被挂在了 nums 的下标上。然后通过 p 指针来加 nums 的元素
        Query& q = queries[i];
        for (; p <= q.r; p++) { // 把 [p, r] 的部分也加进去
            int x = nums[p];
            if (pos[x] != -1) {
                modify(pos[x], -1);
            }
            pos[x] = p; // 更新 x 这个值的最右出现位置，表示 pos[x] 这个位置有个贡献元素，值为 x
            modify(p, 1);
        }
        ans[q.id] = query(q.l, q.r);
    }
    for (int i = 0; i < m; i++) {
        wr(ans[i]); putchar('\n');
    }
    return 0;
}
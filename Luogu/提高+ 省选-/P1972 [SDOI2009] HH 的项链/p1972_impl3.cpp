/*
url: https://www.luogu.com.cn/problem/P1972
参考: https://www.luogu.com.cn/article/j7n2fv29
标签: 离线, 扫描线, 树状数组, 差分
*/

// 把 impl2 的线段树改成用树状数组，用时会变小

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

int tree[maxn + 1];

int lowbit(int x) { return x & -x; }

void modify(int index, int diff) {
    for (int i = index + 1; i < n + 1; i += lowbit(i)) {
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
            modify(y, 1);
        }
        else if (type == 1) {
            ans[id] += query(0, y);
        }
        else ans[id] -= query(0, y);
    }
    for (int i = 0; i < m; i++) {
        wr(ans[i]); putchar('\n');
    }
    return 0;
}
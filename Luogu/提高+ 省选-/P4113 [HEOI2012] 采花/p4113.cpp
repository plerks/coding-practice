/*
url: https://www.luogu.com.cn/problem/P4113
参考: https://www.luogu.com.cn/article/1gdjwagl
相关: 洛谷P1972. HH 的项链, smqyojP435
*/

/* 用 洛谷P1972. HH 的项链 / p1972.cpp 里的那个思路，为了求出现频率 >= 2 的元素种数，只记录最靠右的最多两次的出现就好。

将 query 按 r 排序来处理，将计数的贡献算到最右的那个出现上，也就是让 map[最右] = 1，然后用树状数组求 [l, r] 内的和吗？

不行，[l, r] 可能截断出现，例如 x l x r，[l, r] 内并无两次出现。

但是参考题解，还是能用这个思路做，将贡献算到次右的头上就行了，这样就能保证当 [l, r] 内有个位置 map[i] = 1，nums[i] 确实有在 [l, r] 内出现两次
*/

#include <bits/stdc++.h>

using namespace std;

struct Query {
    int l, r, id;
};

bool cmp(const Query& a, const Query& b) {
    return a.r < b.r;
}

const int maxn = 2e6 + 2;

int n, color, m;

int nums[maxn]; // nums 从 1 开始放

Query queries[maxn];

pair<int, int> map[maxn]; // map[x] 表示当前值x的 (次右，最右) 两次出现位置，还没出现就是 0。可以不用 pair，用 last[i] 和 last[last[i]] 就能记录，见参考题解

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

int query(int L, int R) {
    return pre_sum(R) - pre_sum(L - 1);
}

int ans[maxn];

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> color >> m;
    for (int i = 1; i <= n; i++) cin >> nums[i];
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = {l, r, i};
    }
    sort(queries, queries + m, cmp);
    int p = 1; // nums[1, p) 已被维护，注意这里 nums 下标从 1 开始
    for (int i = 0; i < m; i++) { // 枚举 queries，可以看做扫描线在扫 queries 的下标(或者说 queries 的 r)，归根结底都是在扫 nums 的下标，而 query 根据自己的 r 被挂在了 nums 的下标上。然后通过 p 指针来加 nums 的元素
        auto [l, r, id] = queries[i];
        for (; p <= r; p++) {
            int x = nums[p];
            if (::map[x].second == 0) { // 0 次出现
                ::map[x].second = p;
                modify(::map[x].first, -1); // 如果 first 是 0 ，也不会影响，相当于哨兵
            }
            else { // 1 / 2 次出现
                modify(::map[x].first, -1);
                ::map[x].first = ::map[x].second;
                ::map[x].second = p;
                modify(::map[x].first, 1);
            }
        }
        ans[id] = query(l, r);
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
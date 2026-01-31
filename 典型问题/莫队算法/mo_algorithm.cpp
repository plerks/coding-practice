/*
# 描述 

对于序列上的区间查询问题，区间长度为 n，查询次数为 m，且 n ~ m (以下按 n = m 默认) 。
如果从 [l, r] 的答案能够 O(1) 扩展到 [l - 1, r], [l + 1, r], [l, r - 1], [l, r + 1] （即与
[l, r] 相邻的区间），那么莫队算法采取离线的方式进行处理，先把所有query采集完，然后按特定的顺序处理queries，能够达到在
O(n * sqrt(n)) 时间求出所有查询的答案。

由于可以 O(1) 转移到相邻区间，我们的思想为枚举 query 时，让枚举的 query 区间相近。

分块，按块长度为 sqrt(n) 将 nums 分为 sqrt(n) 块。[l, r] 视作 [l / BLOCK_SIZE, r]，然后对 queries 按区间排序，
也即按 [块号，r] 的两级优先级排序。

然后按顺序处理排序后的 query 并直接按朴素方式转移，总的时间就能是 O(n * sqrt(n))，而非 O(n^2) 。

# 时间复杂度

时间复杂度为 O(n * sqrt(n))

假设块大小为 S ，则共有 n / S 个块，共 m 次查询。

按以上顺序枚举并移动 l, r 的过程中，对于同一个块内的复数次移动（一轮），r 的移动一定是单调的，最多从 0 到 n 移动完整的 n 长度 。于是 r 的总代价最多为 n * (n / S)

对于 l 的移动，则不一定单调，但是除了一轮开头的那次可能是 2S ，其它都是在当前块内的，单次 l 移动代价最多 S 。于是 l 的总代价最多为 mS + (n / S) * 2S

总的代价上界为 n^2 / S + mS + 2n，把 2S 丢掉，上界简化为 n^2 / S + mS，最小值在 S = n / sqrt(m) 时取到，
这就是 n ~ m 时要取 S = sqrt(n) 以及最终时间复杂度为 O(n * sqrt(n)) 的原因。

对于其它 n, m 的大小相对情况，按 n^2 / S + mS 的公式算即可。

# 奇偶化排序优化

直接贴oiwiki原话：

奇偶化排序即对于属于奇数块的询问，r 按从小到大排序，对于属于偶数块的排序，r 从大到小排序，这样我们的 r 指针在处理完这个奇数块的问题后，
将在返回的途中处理偶数块的问题，再向 n 移动处理下一个奇数块的问题，优化了 r 指针的移动次数，一般情况下，这种优化能让程序快 30% 左右．

# 参考

https://oi-wiki.org/misc/offline/

https://oi-wiki.org/misc/mo-algo/

# 相关

* https://www.smqyoj.com/p/ecnu20171F (本文件的代码是针对这个题的)

    给一个长度为 n 的序列 a_1, a_2, ... , a_n 。现有 q 次询问，每次询问有两个数，分别为 l 和 r，求 a_l, ... , a_r 中有多少个不同的数恰好出现了两次。

    题面上 n, q 的范围是 5e5，n * sqrt(n) 处于 1e8 的量级，实际能过，但是洛谷P1972, 4113是1e6的范围，就无法用莫队了。

* 洛谷P1972. HH 的项链

    莫队的问题类型，但是用莫队过不了。

* 洛谷P4113. 采花
*/

#include <bits/stdc++.h>

using namespace std;

/// ┌──────────────────────────── Mo algorithm template begin ────────────────────────────┐
/// 要求外部初始化 nums, queries，写好 move 函数，并调用 mo_solve() 进行计算
/// 答案写在 ans 中
int n, m; /// n 为 nums 大小，m 为 queries 大小
const int maxn = 5e5 + 1;

struct Query {
    int l, r, id;
};

int BLOCK_SIZE;

bool operator<(const Query& x, const Query& y) {
    int block_x = x.l / BLOCK_SIZE;
    int block_y = y.l / BLOCK_SIZE;
    if (block_x != block_y) return block_x < block_y;
    return (block_x & 1) ? x.r < y.r : x.r > y.r; // 奇偶化排序优化
}

int nums[maxn]; /// 数组元素
Query queries[maxn]; /// 查询

int l = 0, r = -1; // 当前的区间 [l, r]

/// 根据题目具体情况自定义 move 维护逻辑
int freq[maxn]; // 用数组作为 map，直接用 std::map 常数太大过不了
int nowAns; // 当前的答案，即区间内频率为 2 的元素个数
/// 移动区间的 l, r，pos 表示增加 / 删除的元素位置，sign 为 1 表示增加了 pos 位置元素，sign 为 -1 表示删除了 pos 位置元素
void move(int pos, int sign) {
    int x = nums[pos];
    if (freq[x] == 2) nowAns--;
    freq[x] += sign;
    if (freq[x] == 2) nowAns++;
}

vector<int> ans;
void mo_solve() {
    BLOCK_SIZE = int(ceil(pow(n, 0.5)));
    sort(queries, queries + m);
    for (int i = 0; i < m; i++) {
        const Query &q = queries[i];
        // 这4个循环的顺序对某些题目不能随便修改，否则移动指针可能出现加入次数是负数的情况，对某些题目可能有问题，具体见oiwiki
        // 记忆的话只需记住把扩大区间的 while 写在前面（先写 add 再 del）
        while (l > q.l) move(--l, 1);
        while (r < q.r) move(++r, 1);
        while (l < q.l) move(l++, -1);
        while (r > q.r) move(r--, -1);
        ans[q.id] = nowAns;
    }
}
/// └──────────────────────────── Mo algorithm template end   ────────────────────────────┘

int temp[maxn];

signed main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = temp[i] = x;
    }
    // nums[i] 的范围是 1e9，导致莫队中必须用 std::map 而不能用数组作为 map，但是 nums 的元素个数只有 5e5 ，因此将其离散化
    sort(temp, temp + n);
    int pos = unique(temp, temp + n) - temp;
    for (int i = 0; i < n; i++) {
        nums[i] = lower_bound(temp , temp + pos, nums[i]) - temp;
    }

    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r; l--, r--; // 编号从 1 开始的
        queries[i] = {l, r, i}; // (l, r, 查询的编号)
    }
    ans.resize(m);
    mo_solve();
    for (auto a : ans) {
        cout << a << '\n';
    }
    return 0;
}

/*
样例输入:
5 2
0 0 1 1 2
3 3
1 5
*/

// 在 smqyoj 上测试，用全局vector比用全局数组慢不少，所以这里只贴了用全局数组的写法
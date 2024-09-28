/*
url: https://leetcode.cn/problems/booking-concert-tickets-in-groups/description/?envType=daily-question&envId=2024-09-28
参考: https://leetcode.cn/problems/booking-concert-tickets-in-groups/solutions/1523876/by-endlesscheng-okcu/
标签: 线段树, 线段树二分, 线段树同时维护两个性质
*/

#include <bits/stdc++.h>

using namespace std;

// 这题能感觉出来要用线段树，但是没注意到占据了的座位一定都从每行开头开始，还以为会有很多个散乱的空闲区间，然后就不知道怎么做了

/* gather()和scatter()，对每行都是从左到右占据座位，所以每行的座位不会出现空位分散的情况，一定都在后缀的位置，
所以每行只需要知道坐了多少人就可以知道当前行的情况。

用线段树维护每行坐了多少人，对于gather，需要知道最左的<= m - k的数字，对于scatter，需要知道前maxRow的空位是否足够，然后修改线段树。
线段树需要同时维护区间最小值和区间sum
*/

class BookMyShow {
public:
    int n, m;
    vector<int> min;
    vector<long long> sum;

    BookMyShow(int n, int m) : n(n), m(m), min(4 * n), sum(4 * n) {
        // 初始时刻坐人数量全是0，不用特别写min和sum
    }
    
    vector<int> gather(int k, int maxRow) {
        // 找第一个已填充小于等于 m - k 的数字
        int r = findFirst(1, 0, n - 1, maxRow, m - k);
        if (r == -1) return {};
        int c = querySum(1, 0, n - 1, r, r); // 求这行坐了多少人，从而知道从哪列开始坐人
        update(1, 0, n - 1, r, k); // r位置加上k
        return {r, c};
    }

    // 在[0, maxRow]找第一个小于等于x的数字，如果没有则返回-1
    int findFirst(int p, int s, int t, int maxRow, int x) {
        if (min[p] > x) {
            return -1;
        }
        if (s == t) return s;
        // 要求的数字存在，在线段树上二分，优先往左边求
        int m = (s + t) / 2;
        if (min[p * 2] <= x) {
            return findFirst(p * 2, s, m, maxRow, x);
        }
        else if (m + 1 <= maxRow) {
            return findFirst(p * 2 + 1, m + 1, t, maxRow, x);
        }
        else return -1;
    }

    // 单点更新，加上k
    void update(int p, int s, int t, int r, int k) {
        if (s == t) {
            min[p] += k;
            sum[p] += k;
            return;
        }
        int m = (s + t) / 2;
        if (r <= m) {
            update(p * 2, s, m, r, k);
        }
        else update(p * 2 + 1, m + 1, t, r, k);
        // 往上更新
        min[p] = std::min(min[2 * p], min[2 * p + 1]);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }

    // 单点求和
    long long querySum(int p, int s, int t, int L, int R) {
        if (L <= s && t <= R) {
            return sum[p];
        }
        long long sum = 0;
        int m = (s + t) / 2;
        if (L <= m) sum += querySum(p * 2, s, m, L, R);
        if (R > m) sum += querySum(p * 2 + 1, m + 1, t, L, R);
        return sum;
    }
    
    bool scatter(int k, int maxRow) {
        if ((long long)(maxRow + 1) * m - querySum(1, 0, n - 1, 0, maxRow) < k) { // 剩余空位不足
            return false;
        }
        int r = findFirst(1, 0, n - 1, maxRow, m - 1); // 找有空位的
        while (k > 0) {
            int x = std::min(m - querySum(1, 0, n - 1, r, r), (long long)k);
            update(1, 0, n - 1, r, x);
            k -= x;
            r++;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    BookMyShow bookMyShow(2, 5);
    auto a = bookMyShow.gather(4, 0);
    auto b = bookMyShow.gather(2, 0);
    auto c = bookMyShow.scatter(5, 1);
    auto d = bookMyShow.scatter(5, 1);
    return 0;
}

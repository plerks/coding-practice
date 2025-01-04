/*
url: https://leetcode.cn/problems/my-calendar-iii/description/?envType=daily-question&envId=2025-01-04
相关: LeetCode729. 我的日程安排表 I, LeetCode731. 我的日程安排表 II
标签: 动态开点线段树, 差分数组
*/

#include <bits/stdc++.h>

using namespace std;

// 和 LeetCode731. 我的日程安排表 II 一样

// 用差分数组，执行用时20ms
class MyCalendarThree {
public:
    map<int, int> map;

    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        map[start]++;
        map[end]--;
        int time = 0; // 预订次数
        int mx = 0;
        for (auto &[_, count] : map) {
            time += count;
            mx = max(mx, time);
        }
        return mx;
    }
};

// 用线段树，执行用时700ms
class MyCalendarThree2 {
public:
    // 区间求max 和 区间加1 的动态开点线段树
    unordered_map<int, int> tree, lazy;

    MyCalendarThree2() {
        
    }

    // 查询[0, 1e9]最大值
    int query(int L, int R, int s, int t, int p) {
        if (t < L || s > R) return 0;

        if (L <= s && t <= R) {
            return tree[p];
        }

        // 需要递归子问题，先将懒惰标记下压
        if (s != t && lazy.count(p)) {
            tree[2 * p] += lazy[p];
            lazy[2 * p] += lazy[p];
            tree[2 * p + 1] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
            lazy[p] = 0;
        }

        int m = (s + t) / 2;
        return max(query(L, R, s, m, p * 2), query(L, R, m + 1, t, 2 * p + 1));
    }

    // 区间加1
    void update(int L, int R, int s, int t, int p) {
        if (t < L || s > R) return;

        if (L <= s && t <= R) {
            tree[p]++;
            lazy[p]++;
            return;
        }

        // 需要递归子问题，先将懒惰标记下压
        if (s != t && lazy.count(p)) {
            tree[2 * p] += lazy[p];
            lazy[2 * p] += lazy[p];
            tree[2 * p + 1] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
            lazy[p] = 0;
        }

        int m = (s + t) / 2;
        update(L, R, s, m, p * 2);
        update(L, R, m + 1, t, 2 * p + 1);

        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }
    
    int book(int start, int end) {
        update(start, end - 1, 0, 1e9, 1);
        return query(0, 1e9, 0, 1e9, 1);
    }
};

int main(int argc, char const *argv[]) {
    MyCalendarThree mct;
    cout << mct.book(10, 20) << endl;
    cout << mct.book(50, 60) << endl;
    cout << mct.book(10, 40) << endl;
    cout << mct.book(5, 15) << endl;
    cout << mct.book(5, 10) << endl;
    cout << mct.book(25, 55) << endl;

    cout << "------" << endl;

    MyCalendarThree2 mct2;
    cout << mct2.book(10, 20) << endl;
    cout << mct2.book(50, 60) << endl;
    cout << mct2.book(10, 40) << endl;
    cout << mct2.book(5, 15) << endl;
    cout << mct2.book(5, 10) << endl;
    cout << mct2.book(25, 55) << endl;

    return 0;
}
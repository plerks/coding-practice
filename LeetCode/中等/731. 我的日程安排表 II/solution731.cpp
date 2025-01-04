/*
url: https://leetcode.cn/problems/my-calendar-ii/description/?envType=daily-question&envId=2025-01-03
参考: https://leetcode.cn/problems/my-calendar-ii/solutions/1678660/wo-de-ri-cheng-an-pai-biao-ii-by-leetcod-wo6n/
相关: LeetCode729. 我的日程安排表 I, LeetCode732. 我的日程安排表 III
标签: 动态开点线段树, 差分数组
*/
#include <bits/stdc++.h>

using namespace std;

class MyCalendarTwo {
public:
    // 我的解法，类似LeetCode729. 我的日程安排表 I，用线段树。执行用时900ms，时间复杂度O(nlog(1e9))，n为book()被调用的次数
    // 一个点不能被>=3个区间包含，用区间求max + 区间add的线段树
    unordered_map<int, int> tree, lazy; // tree表示区间max，lazy表示区间增量

    MyCalendarTwo() {
        
    }

    // 区间求max
    int query(int L, int R, int s, int t, int p) {
        if (t < L || s > R) return 0;

        if (L <= s && t <= R) {
            return tree[p];
        }

        int m = (s + t) / 2;

        // 需要递归子问题才能解决，于是需要懒惰标记下放
        // 懒惰标记下放
        if (s != t && lazy.count(p)) {
            tree[p * 2] += lazy[p];
            lazy[p * 2] += lazy[p];
            tree[p * 2 + 1] += lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            lazy[p] = 0;
        }

        return max(query(L, R, s, m, p * 2), query(L, R, m + 1, t, p * 2 + 1));
    }

    // 区间 + 1
    void update(int L, int R, int s, int t, int p) {
        if (t < L || s > R) return;

        if (L <= s && t <= R) {
            tree[p]++; // tree[p]的值是结合了lazy的，是最新的
            lazy[p]++;
            return;
        }

        int m = (s + t) / 2;

        // 懒惰标记下放
        if (s != t && lazy.count(p)) {
            tree[p * 2] += lazy[p];
            lazy[p * 2] += lazy[p];
            tree[p * 2 + 1] += lazy[p];
            lazy[p * 2 + 1] += lazy[p];
            lazy[p] = 0;
        }

        update(L, R, s, m, p * 2);
        update(L, R, m + 1, t, p * 2 + 1);

        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }
    
    bool book(int start, int end) {
        if (query(start, end - 1, 0, 1e9, 1) >= 2) {
            return false;
        }
        // 区间加1
        update(start, end - 1, 0, 1e9, 1);
        return true;
    }
};

// 官方题解解法一，直接暴力就能过，执行用时20ms，时间复杂度O(n^2)，n为book()被调用的次数
class MyCalendarTwo2 {
public:
    vector<pair<int, int>> booked; // 已经被预订的区间
    vector<pair<int, int>> overlap; // 被预订了2次的交集区间(已经交过一次的)

    MyCalendarTwo2() {
        
    }
    
    bool book(int start, int end) {
        for (auto &[l, r] : overlap) {
            if (!(end <= l || start >= r)) return false;
        }
        for (auto &[l, r] : booked) {
            if (!(end <= l || start >= r)) {
                overlap.emplace_back(max(l, start), min(r, end));
            }
        }
        booked.emplace_back(start, end);
        return true;
    }
};

// 官方题解解法二，用差分数组记录每个点的被预订次数变化量。执行用时111ms，时间复杂度O(n^2)，n为book()被调用的次数
class MyCalendarTwo3 {
public:
    // 用差分数组，count[x]表示点x的预订次数相比前一个位置的变化量(差分)
    /* 差分能优化的原因在于，我想要求的是点x被预订的次数，当一个点被预订后，整个区间的预订次数都会增加1，需要记录整个区间的情况，
    但是使用差分，同样知道完整的信息，但是只需记录两个端点即可。
    */
    map<int, int> count;

    MyCalendarTwo3() {
        
    }
    
    bool book(int start, int end) {
        count[start]++;
        count[end]--;
        int time = 0; // 当前预订次数
        for (auto& [_, diff] : count) { // 这里需要按顺序读取所有端点，所以要用map
            time = time + diff;
            if (time >= 3) {
                count[start]--;
                count[end]++;
                return false;
            }
        }
        return true;
    }
};

// 官方题解解法三即为线段树的解法

int main(int argc, char const *argv[]) {
    MyCalendarTwo mct;
    cout << mct.book(10, 20) << endl;
    cout << mct.book(50, 60) << endl;
    cout << mct.book(10, 40) << endl;
    cout << mct.book(5, 15) << endl;
    cout << mct.book(5, 10) << endl;
    cout << mct.book(25, 55) << endl;

    cout << "------" << endl;

    MyCalendarTwo2 mct2;
    cout << mct2.book(10, 20) << endl;
    cout << mct2.book(50, 60) << endl;
    cout << mct2.book(10, 40) << endl;
    cout << mct2.book(5, 15) << endl;
    cout << mct2.book(5, 10) << endl;
    cout << mct2.book(25, 55) << endl;

    cout << "------" << endl;

    MyCalendarTwo3 mct3;
    cout << mct3.book(10, 20) << endl;
    cout << mct3.book(50, 60) << endl;
    cout << mct3.book(10, 40) << endl;
    cout << mct3.book(5, 15) << endl;
    cout << mct3.book(5, 10) << endl;
    cout << mct3.book(25, 55) << endl;
    return 0;
}

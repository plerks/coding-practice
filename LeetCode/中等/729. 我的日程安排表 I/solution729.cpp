/*
url: https://leetcode.cn/problems/my-calendar-i/description/?envType=daily-question&envId=2025-01-02
参考: https://leetcode.cn/problems/my-calendar-i/solutions/1643942/wo-de-ri-cheng-an-pai-biao-i-by-leetcode-nlxr/
相关: LeetCode731. 我的日程安排表 II, LeetCode732. 我的日程安排表 III
标签: 二分, 动态开点线段树
*/
#include <bits/stdc++.h>

using namespace std;

// 这题应该也能像LeetCode731, 732那样用差分数组
class MyCalendar {
public:
    set<pair<int, int>> intervals;

    MyCalendar() {

    }
    
    // 我的解法
    bool book(int startTime, int endTime) {
        auto it = intervals.lower_bound(make_pair(startTime, endTime));
        if (it != intervals.end()) {
            if (!(endTime <= (*it).first || startTime >= (*it).second)) {
                return false;
            }
        }
        if (it != intervals.begin()) {
            it--;
            if (!(endTime <= (*it).first || startTime >= (*it).second)) {
                return false;
            }
        }
        intervals.insert(make_pair(startTime, endTime));
        return true;
    }

    // 官方题解解法一的写法，更简单点
    bool book_implementation2(int startTime, int endTime) {
        auto it = intervals.lower_bound({endTime, 0}); // 最后一个不相交的区间
        // 检查最后一个不相交的区间的前一个
        if (it == intervals.begin() || (--it)->second <= startTime) {
            intervals.emplace(startTime, endTime);
            return true;
        }
        return false;
    }
};

class MyCalendar2 {
public:
    /* 官方题解解法二，用动态开点线段树，用0,1维护[0, 1e9]每个点是否占用，加入区间时，只需对[startTime, endTime]求和
    即可知道是否区间已有点被占用
    */
    unordered_set<int> tree, lazy; // tree表示区间是否有1，lazy记录这个区间是否已经完全为1了

    MyCalendar2() {
        
    }

    // 查询区间是否含有1
    bool query(int L, int R, int s, int t, int p) {
        if (R < s || L > t) return false;

        if (lazy.count(p)) return true;

        if (L <= s && t <= R) return tree.count(p);

        int mid = (s + t) / 2;

        // 在最开头判断[L, R]和[s, t]是否相交，这里递归时不用判断了
        return query(L, R, s, mid, p * 2) || query(L, R, mid + 1, t, p * 2 + 1);
    }

    // 把区间全变为1
    void update(int L, int R, int s, int t, int p) {
        if (R < s || L > t) return;

        if (L <= s && t <= R) {
            // tree.insert(p); // 更新tree不是必要的，会先检查lazy
            lazy.insert(p);
            return;
        }
        
        int mid = (s + t) / 2;
        update(L, R, s, mid, p * 2);
        update(L, R, mid + 1, t, p * 2 + 1);
        tree.insert(p);
        // 向上合并lazy，以更快查找到结果
        if (lazy.count(p * 2) && lazy.count(p * 2 + 1)) {
            lazy.insert(p);
        }
    }
    
    bool book(int startTime, int endTime) {
        if (query(startTime, endTime - 1, 0, 1e9, 1)) {
            return false;
        }
        // 把区间全改成1
        update(startTime, endTime - 1, 0, 1e9, 1);
        return true;
    }
};

int main(int argc, char const *argv[]) {
    MyCalendar mc;
    cout << mc.book(10, 20) << endl;
    cout << mc.book(15, 25) << endl;
    cout << mc.book(20, 30) << endl;

    MyCalendar2 mc2;
    cout << mc2.book(10, 20) << endl;
    cout << mc2.book(15, 25) << endl;
    cout << mc2.book(20, 30) << endl;
    return 0;
}

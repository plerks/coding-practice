/*
url: https://leetcode.cn/problems/snapshot-array/
相关: LeetCode981. 基于时间的键值存储
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

// 这题还挺有意思

class SnapshotArray {
public:
    vector<vector<pair<int, int>>> history; // (快照编号, 值)
    int id;

    SnapshotArray(int length) : history(length, vector<pair<int, int>>(1)), id(0) {
        
    }
    
    void set(int index, int val) {
        if (history[index].back().first == id) history[index].back().second = val;
        else history[index].push_back({id, val});
    }
    
    int snap() {
        int t = id++;
        return t;
    }
    
    int get(int index, int snap_id) {
        // 二分查找最后一个<=snap_id的
        auto &vec = history[index];
        int idx = lower_bound(vec.begin(), vec.end(), snap_id, [&](const auto &p, int snap_id) {
            return p.first <= snap_id;
        }) - vec.begin() - 1; // 按题目意思snap_id一定合法
        return vec[idx].second;
    }
};

int main(int argc, char const *argv[]) {
    SnapshotArray sa(3);
    sa.set(0, 5);
    cout << sa.snap() << endl;
    sa.set(0, 6);
    cout << sa.get(0, 0) << endl;
    return 0;
}
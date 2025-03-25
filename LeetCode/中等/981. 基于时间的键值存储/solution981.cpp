/*
url: https://leetcode.cn/problems/time-based-key-value-store/
相关: LeetCode1146. 快照数组
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class TimeMap {
public:
    unordered_map<string, vector<pair<int, string>>> history;
    int id = 0;

    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        history[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto &vec = history[key];
        // 寻找最后一个<=timestamp
        int index = lower_bound(vec.begin(), vec.end(), timestamp, [&](const auto &p, int timestamp) {
            return p.first <= timestamp;
        }) - vec.begin() - 1; // vec为空不需要做特殊判断，会是-1
        if (index == -1) return "";
        return vec[index].second;
    }
};

int main(int argc, char const *argv[]) {
    TimeMap tm;
    tm.set("foo", "bar", 1);
    cout << tm.get("foo", 1) << endl;
    cout << tm.get("foo", 3) << endl;
    tm.set("foo", "bar2", 4);
    cout << tm.get("foo", 4) << endl;
    cout << tm.get("foo", 5) << endl;
    return 0;
}
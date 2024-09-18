/*
url: https://leetcode.cn/problems/the-latest-time-to-catch-a-bus/description/?envType=daily-question&envId=2024-09-18
LeetCode参考: https://leetcode.cn/problems/the-latest-time-to-catch-a-bus/solutions/1658352/pai-xu-by-endlesscheng-h9w9/
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2332 {
public:
    // 我的写法，逻辑弄得有点复杂
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> b;
        priority_queue<int, vector<int>, greater<int>> p;
        for (auto &t : buses) {
            b.push({t, 0}); // [车出发时间, 载客量]
        }
        for (auto &t : passengers) {
            p.push(t);
        }
        vector<int> get_on; // 上车时间
        pair<int, int> bus;
        while (!b.empty()) {
            bus = b.top();
            b.pop();
            while (!p.empty() && p.top() <= bus.first && bus.second < capacity) {
                bus.second++;
                get_on.push_back(p.top());
                p.pop();
            }
        }
        // 坐最后一辆车的空位
        if (bus.second < capacity && (get_on.empty() || get_on.back() < bus.first)) return bus.first;
        int ans = get_on.front() - 1;
        // 从后往前找第一个空位，插队
        for (int i = get_on.size() - 1; i > 0; i--) {
            if (i == 0) {
                ans = get_on.front() - 1;
                break;
            }
            if (get_on[i - 1] < get_on[i] - 1) {
                ans = get_on[i] - 1;
                break;
            }
        }
        return ans;
    }

    // 灵茶山艾府解法
    int latestTimeCatchTheBus_implementation2(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        int i = 0, c = 0;
        for (int t : buses) {
            // 接人
            for (c = 0; c < capacity && i < passengers.size() && passengers[i] <= t; c++) {
                i++;
            }
        }
        i--; // i现在指向最后一个上车的人的编号
        // 最后一辆车没装满则从最后一辆车的出发时间开始往前找插队，装满了则从最后一个人的上车时间开始找插队
        int ans = c < capacity ? buses.back() : passengers[i];
        while (i >= 0 && ans == passengers[i]) {
            ans--;
            i--;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2332 solu;
    /* vector<int> buses = {20,30,10};
    vector<int> passengers = {19,13,26,4,25,11,21};
    int capacity = 2; */
    /* vector<int> buses = {3};
    vector<int> passengers = {2, 4};
    int capacity = 2; */
    /* vector<int> buses = {3};
    vector<int> passengers = {2, 3};
    int capacity = 2; */
    /* vector<int> buses = {3};
    vector<int> passengers = {4};
    int capacity = 1; */
    vector<int> buses = {5};
    vector<int> passengers = {2, 3};
    int capacity = 10000;
    cout << solu.latestTimeCatchTheBus(buses, passengers, capacity) << endl;
    cout << solu.latestTimeCatchTheBus_implementation2(buses, passengers, capacity) << endl;
    return 0;
}
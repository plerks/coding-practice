/*
url: https://leetcode.cn/problems/car-fleet/
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution853 {
public:
    // 这样虽然用了double，但是可以通过
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, int>> cars;
        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }
        // 按起点离终点最近，速度最大来排序
        sort(cars.rbegin(), cars.rend());
        int ans = 0;
        double max_t = 0;
        // 若离起点远的到达时间更短，则其并入前面，且其到达时间也变慢
        for (int i = 0; i < n; i++) {
            auto [p, s] = cars[i];
            double t = (target - p) / (double)s;
            if (t <= max_t) { // 前面的车慢，当前车会被合并，不产生新的车队

            }
            else {
                ans++;
                max_t = t;
            }
        }
        return ans;
    }

    // 换一种方式，避开精度隐患
    int carFleet_implementation2(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, int>> cars;
        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }
        // 按起点离终点最近，速度最大来排序
        sort(cars.rbegin(), cars.rend());
        int ans = 0;
        pair<int, int> max_t = {0, 1};
        // 若离起点远的到达时间更短，则其并入前面，且其到达时间也变慢
        for (int i = 0; i < n; i++) {
            auto [p, s] = cars[i];
            pair<int, int> t = {target - p, s};
            if ((target - p) * 1LL * max_t.second <= max_t.first * 1LL * s) { // 前面的车慢，当前车会被合并，不产生新的车队

            }
            else {
                ans++;
                max_t = t;
            }
        }
        return ans;
    }

    // 这题用不上单调栈，要用的话可以这样用
    int carFleet_implementation3(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, int>> cars;
        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }
        // 按起点离终点远到近，速度大到小来排序，不过这题保证position中每个值都不同，第二个排序维度无需关注
        sort(cars.begin(), cars.end());
        stack<pair<int, int>> st;
        for (int i = 0; i < n; i++) {
            auto [p, s] = cars[i];
            // 栈顶为最慢的
            while (!st.empty() && (target - st.top().first) * 1LL * s <= (target - p) * 1LL * st.top().second) { // 若当前车慢，则要合并后方的快车
                st.pop();
            }
            st.push(cars[i]);
        }
        return st.size();
    }
};

int main(int argc, char const *argv[]) {
    Solution853 solu;
    cout << solu.carFleet(12, *new vector<int>{10,8,0,5,3}, *new vector<int>{2,4,1,1,3}) << endl;
    cout << solu.carFleet(10, *new vector<int>{8,3,7,4,6,5}, *new vector<int>{4,4,4,4,4,4}) << endl;

    cout << solu.carFleet_implementation2(12, *new vector<int>{10,8,0,5,3}, *new vector<int>{2,4,1,1,3}) << endl;
    cout << solu.carFleet_implementation2(10, *new vector<int>{8,3,7,4,6,5}, *new vector<int>{4,4,4,4,4,4}) << endl;

    cout << solu.carFleet_implementation3(10, *new vector<int>{8,3,7,4,6,5}, *new vector<int>{4,4,4,4,4,4}) << endl;
    return 0;
}
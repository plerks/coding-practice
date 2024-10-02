// https://leetcode.cn/problems/minimum-speed-to-arrive-on-time/?envType=daily-question&envId=2024-10-02

#include <bits/stdc++.h>

using namespace std;

class Solution1870 {
public:
    int minSpeedOnTime(const vector<int>& dist, double hour) {
        // 速度越快，越能在hour内到达，二分答案，区间从否到是，搜索第一个是
        int mx = *max_element(dist.begin(), dist.end());
        int left = 1;
        int right = mx * 100; // 如果能到的话，小数点后最多存在两位数字，让speed够大，前面的段用时取整为1，最后一段用时0.01

        auto check = [&](int speed) {
            double t = 0;
            for (int i = 0; i < dist.size() - 1; i++) {
                int d = dist[i];
                t += d / speed;
                t += (d % speed > 0);
            }
            // 最后一段不用化为整数
            t += dist.back() / (double)speed;
            return !(t > hour);
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left == mx * 100 + 1 ? -1 : left;
    }
};

int main(int argc, char const *argv[]) {
    Solution1870 solu;
    vector<int> dist = {1,3,2};
    double hour = 1.9;
    cout << solu.minSpeedOnTime(dist, hour) << endl;
    cout << solu.minSpeedOnTime({1,1,100000}, 2.01) << endl;
    return 0;
}

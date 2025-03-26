/*
url: https://leetcode.cn/problems/capacity-to-ship-packages-within-d-days/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1011 {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        int mi = INT_MAX, mx = 0;
        for (int x : weights) {
            mi = min(mi, x);
            mx = max(mx, x);
        }

        auto check = [&](int mid) {
            int i = 0, cnt = 0;
            while (i < n) {
                int capacity = mid;
                while (i < n && weights[i] <= capacity) {
                    capacity -= weights[i];
                    i++;
                }
                cnt++;
            }
            return cnt <= days;
        };

        int left = max(mx, (n / days) * mi), right = ((n - 1)/ days + 1) * mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution1011 solu;
    // cout << solu.shipWithinDays(*new vector<int>{1,2,3,4,5,6,7,8,9,10}, 5) << endl;
    cout << solu.shipWithinDays(*new vector<int>{3,2,2,4,1,4}, 3) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/koko-eating-bananas/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution875 {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        int mi = INT_MAX, mx = 0;
        for (int x : piles) {
            mi = min(mi, x);
            mx = max(mx, x);
        }

        auto check = [&](int mid) {
            long long t = 0;
            for (int x : piles) t += (x - 1) / mid + 1;
            return t <= h;
        };

        int left = max(1, n / h * mi), right = mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution875 solu;
    cout << solu.minEatingSpeed(*new vector<int>{3,6,7,11}, 8) << endl;
    return 0;
}
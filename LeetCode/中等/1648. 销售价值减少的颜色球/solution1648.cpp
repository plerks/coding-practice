/*
url: https://leetcode.cn/problems/sell-diminishing-valued-colored-balls/
标签: 【题单】二分算法, 差分
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1648 {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        auto check = [&](int k) {
            long long sum = 0;
            for (int x : inventory) {
                sum += max(0, x - k);
            }
            return sum >= orders;
        };

        int left = 0, right = *max_element(inventory.begin(), inventory.end());
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // left是第一个值，以这条线为分割(包含这条线)，能选出orders个球
        long long ans = 0;
        const int MOD = 1e9 + 7;
        for (int x : inventory) {
            if (x > left) { // [left + 1, x]的全选
                ans = (ans + (left + 1 + x) * 1LL * (x - left) / 2) % MOD;
                orders -= x - left;
            }
        }
        ans = (ans + left * 1LL * orders) % MOD; // 在线上补球

        return ans;
    }

    int maxProfit_implementation2(vector<int>& inventory, int orders) {
        int n = inventory.size();
        sort(inventory.begin(), inventory.end());
        long long sum = 0;
        int edge = 0;
        for (int i = n - 1; i >= 0; i--) {
            long long h = inventory[i] - ((i - 1 < 0) ? 0 : inventory[i - 1]);
            long long w = n - i;
            if (sum + w * h >= orders) {
                int d = (orders - sum + (w - 1)) / w;
                edge = inventory[i] - d + 1; // 题目保证inventory总的球的数量够orders，最后一定会走到这种情况
                break;
            }
            else sum += w * h;
        }
        long long ans = 0;
        const int MOD = 1e9 + 7;
        for (int x : inventory) {
            if (x > edge) {
                ans = (ans + (edge + 1 + x) * 1LL * (x - edge) / 2) % MOD;
                orders -= x - edge;
            }
        }
        ans = (ans + edge * 1LL * orders) % MOD; // 在线上补球

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1648 solu;
    cout << solu.maxProfit(*new vector<int>{2,5}, 4) << endl;
    cout << solu.maxProfit(*new vector<int>{1000000000}, 1000000000) << endl;

    cout << solu.maxProfit_implementation2(*new vector<int>{2,5}, 4) << endl;
    cout << solu.maxProfit_implementation2(*new vector<int>{1000000000}, 1000000000) << endl;
    return 0;
}
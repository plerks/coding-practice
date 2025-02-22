/*
url: https://leetcode.cn/problems/eat-pizzas/
标签: LeetCode第437场周赛, 贪心
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3457 {
public:
    // 周赛时的写法，通过
    long long maxWeight(vector<int>& pizzas) {
        int n = pizzas.size();
        sort(pizzas.begin(), pizzas.end());
        int d = n / 4;
        int odd = (d + 1) / 2; // 奇数天的数量
        int even = d / 2;
        long long ans = 0;
        for (int k = 0; k < odd; k++) {
            ans += pizzas[n - 1 - k];
        }
        for (int k = 0; k < even; k++) {
            ans += pizzas[n - odd - 2 - k * 2];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3457 solu;
    cout << solu.maxWeight(*new vector<int>{1,2,3,4,5,6,7,8}) << endl;
    return 0;
}
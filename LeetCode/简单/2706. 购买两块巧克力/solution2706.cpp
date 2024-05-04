// https://leetcode.cn/problems/buy-two-chocolates/description/

#include <bits/stdc++.h>

using namespace std;

class Solution2706 {
public:
    int buyChoco(const vector<int>& prices, int money) {
        int min = INT_MAX;
        int subMin = INT_MAX;
        for (auto price : prices) {
            if (price <= min) {
                subMin = min;
                min = price;
            }
            else if (price < subMin) {
                subMin = price;
            }
        }
        return money - min - subMin >= 0 ? money - min - subMin : money;
    }
};

int main(int argc, char const *argv[]) {
    Solution2706 solu;
    cout << solu.buyChoco({1,2,2}, 3) << endl;
    return 0;
}

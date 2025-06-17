/*
url: https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1475 {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        stack<int> st;
        vector<int> ans(prices.begin(), prices.end());
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && prices[st.top()] > prices[i]) {
                st.pop();
            }
            ans[i] -= st.empty() ? 0 : prices[st.top()];
            st.push(i);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1475 solu;
    auto a = solu.finalPrices(*new vector<int>{8,4,6,2,3});
    return 0;
}
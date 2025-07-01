/*
url: https://leetcode.cn/problems/find-the-original-array-of-prefix-xor/
标签: 【算法题单】位运算, 异或的性质
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2433 {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();
        vector<int> ans(n);
        int pre = 0;
        for (int i = 0; i < n; i++) {
            ans[i]= pre ^ pref[i];
            pre = pre ^ ans[i];
        }
        return ans;
    }

    // 换一种写法，ans[i] = xor_ans[0, i - 1] ^ pref[i] = ans[i - 1] ^ pref[i - 1] ^ ans[i - 1] ^ pref[i] = pref[i - 1] ^ pref[i]
    vector<int> findArray_implementation2(vector<int>& pref) {
        int n = pref.size();
        vector<int> ans(n);
        ans[0] = pref[0];
        for (int i = 1; i < n; i++) {
            ans[i]= pref[i - 1] ^ pref[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2433 solu;
    auto a = solu.findArray(*new vector<int>{5,2,0,3,1});
    auto b = solu.findArray(*new vector<int>{5,2,0,3,1});
    return 0;
}
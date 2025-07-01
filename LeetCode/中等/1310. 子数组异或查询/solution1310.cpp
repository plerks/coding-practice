/*
url: https://leetcode.cn/problems/xor-queries-of-a-subarray/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1310 {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] ^ arr[i];
        }
        vector<int> ans;
        for (auto &v : queries) {
            int l = v[0], r = v[1];
            ans.push_back(pre[r + 1] ^ pre[l - 1 + 1]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1310 solu;
    auto a = solu.xorQueries(*new vector<int>{1,3,4,8}, *new vector<vector<int>>{{0,1},{1,2},{0,3},{3,3}});
    return 0;
}
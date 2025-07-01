/*
url: https://leetcode.cn/problems/decode-xored-array/
相关: LeetCode1734. 解码异或后的排列
标签: 【算法题单】位运算, 异或的性质
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1720 {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int n = encoded.size() + 1;
        vector<int> ans(n);
        ans[0] = first;
        for (int i = 1; i < n; i++) {
            ans[i] = encoded[i - 1] ^ ans[i - 1];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
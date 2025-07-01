/*
url: https://leetcode.cn/problems/find-the-prefix-common-array-of-two-arrays/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2657 {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        // 1 <= A.length == B.length == n <= 50，1 <= A[i], B[i] <= n，题目保证 A 和 B 两个数组都是 n 个元素的排列。用一个long long压缩
        long long a = 0, b = 0;
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            a |= 1LL << A[i]; // 注意是1LL，不然移位溢出了
            b |= 1LL << B[i];
            ans[i] = __builtin_popcountll(a & b); // __builtin_popcountll，别写成__builtin_popcount
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2657 solu;
    auto a = solu.findThePrefixCommonArray(*new vector<int>{1,3,2,4}, *new vector<int>{3,1,2,4});
    return 0;
}
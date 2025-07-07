/*
url: https://leetcode.cn/problems/circular-permutation-in-binary-representation/
相关: LeetCode89. 格雷编码
标签: 【算法题单】位运算, 格雷码
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1238 {
public:
    vector<int> circularPermutation(int n, int start) {
        int startIndex = -1;
        for (int i = 0; i < (1 << n); i++) {
            if (start == (i ^ (i >> 1))) {
                startIndex = i; // 先求出start值对应的格雷码编号，具体见 LeetCode89. 格雷编码
                break;
            }
        }
        vector<int> ans(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            ans[i] = startIndex ^ (startIndex >> 1);
            startIndex = (startIndex + 1) % (1 << n);
        }
        return ans;
    }

    /* 参考<https://leetcode.cn/problems/circular-permutation-in-binary-representation/solutions/2128016/python3javacgotypescript-yi-ti-shuang-ji-zhm7/>
    不需要两次遍历，首先生成原本的格雷码序列 i ^ (i >> 1)，
    然后gray(0)一定为0，则gray(0) ^ start为start，
    再然后，由于gray(i)和gray(i - 1)只有一位不同，则gray(i) ^ start和gray(i - 1) ^ start一定也只有一位不同。
    于是，只需把 以0开始的格雷码 每个数都异或start，就可以得到 以start开始的格雷码
    */
    vector<int> circularPermutation_implementation2(int n, int start) {
        vector<int> ans(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            ans[i] = i ^ (i >> 1) ^ start;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1238 solu;
    auto a = solu.circularPermutation(2, 3);
    return 0;
}
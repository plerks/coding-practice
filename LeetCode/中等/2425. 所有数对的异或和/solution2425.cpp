/*
url: https://leetcode.cn/problems/bitwise-xor-of-all-pairings/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2425 {
public:
    // 我的解法，拆位来算，搞复杂了
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int cnt_one1[31]{};
        int cnt_one2[31]{};
        for (int i = 0; i <= 30; i++) {
            for (int x : nums1) {
                cnt_one1[i] += (x >> i) & 1;
            }
        }

        for (int i = 0; i <= 30; i++) {
            for (int x : nums2) {
                cnt_one2[i] += (x >> i) & 1;
            }
        }

        int ans = 0;
        for (int i = 0; i <= 30; i++) {
            int c00 = nums1.size() - cnt_one1[i];
            int c01 = cnt_one1[i];
            int c10 = nums2.size() - cnt_one2[i];
            int c11 = cnt_one2[i];
            // ans += (1 << i) * (c00 * c11 + c01 * c10); // 这样写是 nums3 中所有整数的和，题目要求的是 nums3 中所有整数的异或和
            ans += (1 << i) * ((c00 * c11 + c01 * c10) % 2);
        }

        return ans;
    }

    // 参考灵茶题解，是要nums3中所有元素异或，不用拆位。若 n2 为奇数，则最后的异或 nums1[i] 会出现奇数次，否则偶数次，^结果为0
    int xorAllNums_implementation2(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0;
        if (nums2.size() % 2 == 1) for (int x : nums1) ans ^= x;
        if (nums1.size() % 2 == 1) for (int x : nums2) ans ^= x;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2425 solu;
    cout << solu.xorAllNums(*new vector<int>{2,1,3}, *new vector<int>{10,2,5,0}) << endl;

    cout << solu.xorAllNums_implementation2(*new vector<int>{2,1,3}, *new vector<int>{10,2,5,0}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/total-hamming-distance/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution477 {
public:
    // 我的解法
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        int cnt_one[32]{};
        for (int x : nums) {
            for (int i = 0; i < 32; i++) {
                cnt_one[i] += (x >> i) & 1;
            }
        }
        int ans = 0;
        for (int x : nums) {
            for (int i = 0; i < 32; i++) {
                int bit = (x >> i) & 1;
                if (bit) {
                    ans += n - cnt_one[i];
                }
                else {
                    ans += cnt_one[i];
                }
            }
        }
        return ans / 2;
    }

    // 宫水三叶题解解法，统计每位上的0和1的个数相乘就行了
    int totalHammingDistance_implementation2(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int c0 = 0, c1 = 0;
            for (int x : nums) {
                if ((x >> i) & 1) c1++;
                else c0++;
            }
            ans += c0 * c1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution477 solu;
    cout << solu.totalHammingDistance(*new vector<int>{4,14,2}) << endl;
    return 0;
}
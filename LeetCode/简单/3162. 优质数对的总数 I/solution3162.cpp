/*
url: https://leetcode.cn/problems/find-the-number-of-good-pairs-i/description/
相关: LeetCode3164. 优质数对的总数 II
标签: LeetCode第399场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3162 {
public:
    // 这题数组规模不超过50，直接暴力即可。LeetCode3164. 优质数对的总数 II需要优化
    int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((nums1[i] % (nums2[j] * k)) == 0) ans++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

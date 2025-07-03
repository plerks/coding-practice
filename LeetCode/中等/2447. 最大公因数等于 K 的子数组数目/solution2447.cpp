/*
url: https://leetcode.cn/problems/number-of-subarrays-with-gcd-equal-to-k/
标签: 【算法题单】位运算, LogTrick
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2447 {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        int cnt_k = 0; // 以 j 为右边界，有多少个子数组 gcd 为 k
        for (int j = 0; j < n; j++) {
            if (nums[j] == k) cnt_k++;
            for (int i = j - 1; i >= 0; i--) {
                int before = nums[i];
                int now = __gcd(nums[i], nums[j]);
                if (before == now) break;
                if (before == k && now != k) cnt_k--;
                if (before != k && now == k) cnt_k++;
                nums[i] = now;
            }
            ans += cnt_k;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2447 solu;
    cout << solu.subarrayGCD(*new vector<int>{9,3,1,2,6,3}, 3) << endl;
    return 0;
}
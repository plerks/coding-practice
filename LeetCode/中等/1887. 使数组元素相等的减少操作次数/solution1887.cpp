/*
url: https://leetcode.cn/problems/reduction-operations-to-make-the-array-elements-equal/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1887 {
public:
    int reductionOperations(vector<int>& nums) {
        int n = nums.size();
        sort(nums.rbegin(), nums.rend());
        int cnt = 0; // 总共有多少段
        // nums[i]每次往下一个小值跳一步
        for (int i = 0; i < n;) {
            // int start = i;
            i++;
            while (i < n && nums[i] == nums[i - 1]) i++;
            cnt++;
        }
        int ans = 0;
        for (int i = 0; i < n;) {
            int start = i;
            i++;
            while (i < n && nums[i] == nums[i - 1]) i++;
            ans += (i - start) * (cnt - 1);
            cnt--;
        }
        return ans;
    }

    // 官方题解一次循环的解法，前缀长度计数，然后到突变处累加
    int reductionOperations_implementation2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.rbegin(), nums.rend());
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[i - 1]) {
                ans += i; // 前面有i个数要变成nums[i]
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1887 solu;
    cout << solu.reductionOperations(*new vector<int>{5,1,3}) << endl;
    return 0;
}
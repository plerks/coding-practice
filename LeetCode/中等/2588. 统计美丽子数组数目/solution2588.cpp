/*
url: https://leetcode.cn/problems/count-the-number-of-beautiful-subarrays/
相关: LeetCode560. 和为 K 的子数组
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2588 {
public:
    /* 子数组得满足区间内每位的1的个数都为偶数，即区间异或为0。1 <= nums.length <= 10^5，
    所以，求异或的前缀和，并记录异或值的位置。
    */
    long long beautifulSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> map; // (异或值，出现次数)
        long long ans = 0;
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] ^ nums[i];
            ans += map[pre[i + 1]] + (pre[i + 1] == 0);
            map[pre[i + 1]]++;
        }
        return ans;
    }

    /* 灵茶题解写法，写得更简洁。此外， + (pre[i + 1] == 0) 的处理可以通过在map中放一个(0, 1)来实现，
    也就是说map中一开始就有1个0 (对应-1位置)，后面的前缀和pre[i]如果是0，会找到-1作为左端点，即(-1, i]这个子数组，ans会+1。
    或者说，前缀和记录的是[0, i]的和，然后我们用两个前缀和相减找区间，但被减的那个区间可以为空([0, -1]区间)，这个漏了要补进去。
    此题 前缀和+哈希表 的组合在 LeetCode560 中也有用。
    */
    long long beautifulSubarrays_implementation2(vector<int>& nums) {
        long long ans = 0;
        int sum = 0;
        unordered_map<int, int> map{{0, 1}}; // map[0] = 1
        for (int &x : nums) {
            sum ^= x;
            ans += map[sum]++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2588 solu;
    cout << solu.beautifulSubarrays(*new vector<int>{4,3,1,2,4}) << endl;

    cout << solu.beautifulSubarrays_implementation2(*new vector<int>{4,3,1,2,4}) << endl;
    return 0;
}
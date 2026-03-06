/*
url: https://leetcode.cn/problems/count-subarrays-with-k-distinct-integers/
标签: LeetCode第491场周赛
*/
// 这次双周赛三题
#include <bits/stdc++.h>

using namespace std;

class Solution3859 {
public:
    /* 参考灵茶题解，恰好型滑动窗口，看到恰好不好办，改成 {>= k} - {>= k + 1}，
    但是这题还没这么简单，仅仅看数字种数还不行，这题还要求窗口内的数字的出现频率全部都 >= m，
    要维护窗口内的数字的频率都 >= m 也是恰好型的，不好维护，但是可以维护窗口内够频率的数字的个数够多（还是要把恰好变成不等式）。

    不好维护窗口内的数字的频率都 >= m，那就退而求其次维护窗口内频率 >= m 的数字的个数至少有 k 个
    {数字种数 >= k && 频率 >= m 的数字至少有 k 个} - {数字种数 >= k + 1 && 频率 >= m 的数字至少有 k 个} 就是答案
    不过这里有个点，这种维护方式，如果中间夹了频率 < m 的数字会怎么样？
    例如 nums = [3 3 2 2 1], k = 2, m = 2，对 r = 4 时，{数字种数 >= k && 频率 >= m 的数字至少有 k 个} 的 l 在 [0, 0] 范围，
    {数字种数 >= k + 1 && 频率 >= m 的数字至少有 k 个} 的 l 也在 [0, 0] 范围（由于夹了个 1，所以满足数字种数 >= k + 1），夹带的 1 会被抵消，不会导致错误计数。

    这题有两个约束，能以这种方式滑窗，有点奇妙
    */
    long long countSubarrays(vector<int>& nums, int k, int m) {
        return calc(nums, k, k, m) - calc(nums, k + 1, k, m);
    }

    // >= k 种整数，且每个的出现次数都 >= m 的子数组个数
    long long calc(vector<int>& nums, int unique, int k, int m) {
        int n = nums.size();
        int cnt = 0; // 频率 >= m 的数字的个数
        unordered_map<int, int> mp;
        long long ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            mp[nums[r]]++;
            if (mp[nums[r]] == m) cnt++;
            while (mp.size() >= unique && cnt >= k) {
                mp[nums[l]]--;
                if (mp[nums[l]] == m - 1) cnt--;
                if (mp[nums[l]] == 0) mp.erase(nums[l]);
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3859 solu;
    // cout << solu.countSubarrays(*new vector<int>{1,2,1,2,2}, 2, 2) << endl;
    // cout << solu.countSubarrays(*new vector<int>{2,2,2,1,1,2,2,3,3}, 2, 2) << endl;
    cout << solu.countSubarrays(*new vector<int>{2,2,1}, 1, 2) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/get-the-maximum-score/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1537 {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        const int mod = 1e9 + 7;
        unordered_map<int, int> cnt;
        for (int x : nums1) cnt[x]++;
        for (int x : nums2) cnt[x]++;
        unordered_map<int, int> pos1;
        unordered_map<int, int> pos2;
        for (int i = 0; i < nums1.size(); i++) if (cnt[nums1[i]] > 1) pos1[nums1[i]] = i;
        for (int i = 0; i < nums2.size(); i++) if (cnt[nums2[i]] > 1) pos2[nums2[i]] = i;

        vector<vector<long long>> memo(3, vector<long long>(1e5 + 1, -1)); // 这里别忘了是long long
        
        auto dfs = [&](auto& dfs, int chain, int p) -> long long { // 表示从chain这条链上从p开始走能获得的最大收益
            // cout << chain << " " << p << endl;
            if (chain == 1 && p >= nums1.size()) return 0;
            if (chain == 2 && p >= nums2.size()) return 0;
            if (memo[chain][p] != -1) return memo[chain][p];
            // 重复数字只统计一次
            if (chain == 1) {
                long long x = nums1[p];
                long long res = 0;
                if (cnt[x] == 1) {
                    res = x + dfs(dfs, chain, p + 1);
                }
                else res = x + max(dfs(dfs, chain, p + 1), dfs(dfs, chain % 2 + 1, pos2[x] + 1));
                memo[chain][p] = res;
                return res;
            }
            else {
                long long x = nums2[p];
                long long res = 0;
                if (cnt[x] == 1) res = x + dfs(dfs, chain, p + 1);
                else res = x + max(dfs(dfs, chain, p + 1), dfs(dfs, chain % 2 + 1, pos1[nums2[p]] + 1));
                memo[chain][p] = res;
                return res;
            }
        };

        long long ans = max(dfs(dfs, 1, 0), dfs(dfs, 2, 0));
        /* 1 <= nums1.length, nums2.length <= 10^5，1 <= nums1[i], nums2[i] <= 10^7，
        1e5 * 1e7用long long不会溢出，要最后一步才% mod。这题题面要求% mod没有意义，要求最大值，则
        中间过程不能取mod，否则虽然算出来的mod值大，但不一定是最优解的mod结果。所以long long要能装下，不然得高精度了，
        但是long long能装下，最后又没必要要求%mod，直接函数返回long long就行了
        */
        return ans % mod;
    }

    // 改成dp，并用双指针找到所有可能相等的位置对
    int maxSum_implementation2(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        const int mod = 1e9 + 7;
        vector<long long> f1(n + 1);
        vector<long long> f2(m + 1);
        int i = n - 1, j = m - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] == nums2[j]) {
                int x = nums1[i];
                f1[i] = max(x + f1[i + 1], x + f2[j + 1]);
                f2[j] = max(x + f2[j + 1], x + f1[i + 1]);
                i--; j--;
            }
            else if (nums1[i] > nums2[j]) {
                int x = nums1[i];
                f1[i] = x + f1[i + 1];
                i--;
            }
            else {
                int x = nums2[j];
                f2[j] = x + f2[j + 1]; 
                j--;
            }
        }
        while (i >= 0) {
            int x = nums1[i];
            f1[i] = x + f1[i + 1];
            i--;
        }
        while (j >= 0) {
            int x = nums2[j];
            f2[j] = x + f2[j + 1];
            j--;
        }
        return max(f1[0], f2[0]) % mod;
    }
};

int main(int argc, char const *argv[]) {
    Solution1537 solu;
    // cout << solu.maxSum(*new vector<int>{2,4,5,8,10}, *new vector<int>{4,6,8,9}) << endl;
    cout << solu.maxSum(*new vector<int>{1,3,5,7,9}, *new vector<int>{3,5,100}) << endl;

    cout << solu.maxSum_implementation2(*new vector<int>{2,4,5,8,10}, *new vector<int>{4,6,8,9}) << endl;
    cout << solu.maxSum_implementation2(*new vector<int>{1,3,5,7,9}, *new vector<int>{3,5,100}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/subarray-sum-equals-k/
相关: LeetCode2588. 统计美丽子数组数目
*/
#include <bits/stdc++.h>

using namespace std;

class Solution560 {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> map{{0, 1}}; // map[0] = 1
        int sum = 0;
        int ans = 0;
        for (int &x : nums) {
            sum += x;
            auto it = map.find(sum - k);
            ans += it == map.end() ? 0 : it->second; // getOrDefault()，避免使用operator[]的副作用
            map[sum]++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution560 solu;
    cout << solu.subarraySum(*new vector<int>{1,2,3}, 3) << endl;
    return 0;
}
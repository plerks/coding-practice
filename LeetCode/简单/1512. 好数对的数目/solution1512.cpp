/*
url: https://leetcode.cn/problems/number-of-good-pairs/
相关: LeetCode3404. 统计特殊子序列的数目
标签: 动态维护
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1512 {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> map;
        int ans = 0;
        for (int x : nums) {
            ans += map[x];
            map[x]++;
        }
        return ans;
        /* 这题也可以不动态维护，先完整跑一遍，把nums所有元素计数，然后再遍历一遍map，
        每次 ans += count * (count - 1) / 2，时间复杂度上没有区别。
        但是对于像`LeetCode3404. 统计特殊子序列的数目`那样对于同类的元素还需做选择的问题，
        动态维护就会产生本质区别。
        */
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

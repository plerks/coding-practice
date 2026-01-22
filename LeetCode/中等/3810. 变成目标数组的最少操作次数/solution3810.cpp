/*
url: https://leetcode.cn/problems/minimum-operations-to-reach-target-array/
标签: LeetCode第174场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3810 {
public:
    int minOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        unordered_set<int> st;
        for (int i = 0; i < n; i++) {
            if (nums[i] == target[i]) continue;
            st.insert(nums[i]);
        }
        return st.size();
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

// 找出所有子数组 OR 可能出现的值
// 时间复杂度 O(nlogU)，U为数据范围
unordered_set<int> logtrick(vector<int> nums) {
    int n = nums.size();
    unordered_set<int> st;
    // 原地修改 nums
    for (int i = 0; i < n; i++) {
        st.insert(nums[i]);
        for (int j = i - 1; j >= 0; j--) {
            if ((nums[j] | nums[i]) == nums[j]) break;
            nums[j] = nums[j] | nums[i];
            st.insert(nums[j]);
        }
    }
    return st;
}

// 暴力，时间复杂度 O(n^2)
unordered_set<int> brute(vector<int> nums) {
    int n = nums.size();
    unordered_set<int> st;
    for (int i = 0; i < n; i++) {
        int t = nums[i];
        st.insert(t);
        for (int j = i - 1; j >= 0; j--) {
            t |= nums[j];
            st.insert(t);
        }
    }
    return st;
}

int main(int argc, char const *argv[]) {
    vector<int> nums = {5, 4, 1, 0, 9, 7, 123, 11, 3895, 540};
    unordered_set<int> ans = logtrick(nums);
    unordered_set<int> ans_brute = brute(nums);
    return 0;
}
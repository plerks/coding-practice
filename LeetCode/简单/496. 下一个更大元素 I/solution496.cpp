/*
url: https://leetcode.cn/problems/next-greater-element-i/
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution496 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> val_right(nums2.size(), -1);
        unordered_map<int, int> pos;
        for (int i = nums2.size() - 1; i >= 0; i--) {
            pos[nums2[i]] = i;
            while (!st.empty() && nums2[st.top()] <= nums2[i]) {
                st.pop();
            }
            if (!st.empty()) val_right[i] = nums2[st.top()];
            st.push(i);
        }
        vector<int> ans(nums1.size());
        for (int i = 0; i < nums1.size(); i++) {
            ans[i] = val_right[pos[nums1[i]]];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution496 solu;
    auto a = solu.nextGreaterElement(*new vector<int>{4,1,2}, *new vector<int>{1,3,4,2});
    return 0;
}
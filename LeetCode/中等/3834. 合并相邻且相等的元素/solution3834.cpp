/*
url: https://leetcode.cn/problems/merge-adjacent-equal-elements/
标签: LeetCode第488场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3834 {
public:
    // 周赛时的写法，当一个元素要入栈时需要考虑合并，当其合并入栈时仍然需要考虑合并，这个思路的话就得把元素pop出来再考虑
    vector<long long> mergeAdjacent(vector<int>& nums) {
        int n = nums.size();
        vector<long long> st;
        for (int i = 0; i < n; i++) {
            long long x = nums[i];
            while (true) {
                if (st.empty() || st.back() != x) {
                    st.push_back(x);
                    break;
                }
                if (!st.empty() && st.back() == x) {
                    x = st.back() + x;
                    st.pop_back();
                }
                else st.push_back(x);
            }
        }
        return st;
    }

    // 参考灵茶题解，让合并发生在栈顶的两个元素，就能用一个统一的逻辑写
    vector<long long> mergeAdjacent_impl2(vector<int>& nums) {
        int n = nums.size();
        vector<long long> st;
        for (int x : nums) {
            st.push_back(x);
            while (st.size() >= 2 && st.back() == st[st.size() - 2]) {
                st.pop_back();
                st.back() *= 2;
            }
        }
        return st;
    }
};

int main(int argc, char const *argv[]) {
    Solution3834 solu;
    auto a = solu.mergeAdjacent(*new vector<int>{2,1,1,2});
    auto b = solu.mergeAdjacent_impl2(*new vector<int>{2,1,1,2});
    return 0;
}
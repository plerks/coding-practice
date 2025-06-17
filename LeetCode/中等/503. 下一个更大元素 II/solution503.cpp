/*
url: https://leetcode.cn/problems/next-greater-element-ii/
参考: https://leetcode.cn/problems/next-greater-element-ii/solutions/637573/xia-yi-ge-geng-da-yuan-su-ii-by-leetcode-bwam/
标签: 【算法题单】单调栈, 循环数组
*/

#include <bits/stdc++.h>

using namespace std;

class Solution503 {
public:
    vector<int> nextGreaterElements_wrong(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> right(n, -1);
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            if (!st.empty()) right[i] = nums[st.top()];
            st.push(i);
        }
        
        // 求左边最远的比nums[i]大的，注意以下方法是错误的
        // 这个问题场景不能用单调栈，[1,2,3,2,1]这个用例就能看出来，3把2出栈了，然后到最后的1时，st2.front()为nums[2]而非nums[1]
        // 要解决这个问题似乎可以用值域线段树，每个叶子节点对应一个值，存储该值的最小索引。求左边最远的比nums[i]大的，即为求区间[nums[i] + 1, ..)内的最小值
        vector<int> st2;
        vector<int> left(n, -1);
        for (int i = 0; i < n; i++) {
            while (!st2.empty() && nums[st2.back()] <= nums[i]) st2.pop_back();
            if (!st2.empty()) left[i] = nums[st2.front()]; // 求最远的那个
            st2.push_back(i);
        }

        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            if (right[i] != -1) ans[i] = right[i];
            else if (left[i] != -1) ans[i] = left[i];
        }
        return ans;
    }

    // 参考官方题解，这里循环数组的处理方式是，把前n - 1个元素复制一份接到末尾(并不需要实际这么操作)，然后变成单调栈问题
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> ans(n, -1);
        for (int i = 0; i < 2 * n - 1; i++) {
            int x = nums[i % n];
            while (!st.empty() && nums[st.top() % n] < x) {
                ans[st.top() % n] = x;
                st.pop();
            }
            st.push(i); // 也可以这里 i % n，上面 st.top() 就不用 % n 了
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution503 solu;
    // auto a = solu.nextGreaterElements(*new vector<int>{1,2,3,4,3});
    // auto b = solu.nextGreaterElements(*new vector<int>{5,4,3,2,1});
    auto c = solu.nextGreaterElements(*new vector<int>{1,2,3,2,1});
    return 0;
}
/*
url: https://leetcode.cn/problems/132-pattern/
参考: https://leetcode.cn/problems/132-pattern/solutions/676437/132mo-shi-by-leetcode-solution-ye89/
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution456 {
public:
    // 我的解法，枚举中间那个数，和官方题解解法一相同，时间复杂度O(nlogn)
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        vector<int> min_left(n, INT_MAX); // i左侧的最小值
        for (int i = 1; i < n; i++) {
            min_left[i] = min(min_left[i - 1], nums[i - 1]);
        }

        set<int> st;
        // 枚举i作为中间那个数，左边取最小，右边取 < nums[i]的最大值
        for (int i = n - 1; i >= 0; i--) {
            // 搜索右侧最后一个 < nums[i] 的值
            auto it = st.lower_bound(nums[i]);
            if (it != st.begin()) {
                it--;
                if (it != st.end()) {
                    int r = *it;
                    if (r > min_left[i]) return true;
                }
            }
            st.insert(nums[i]);
        }
        return false;
    }

    /* 官方题解解法二，枚举1，单调栈。时间复杂度O(n)
    从右到左枚举1，看nums[i]能否作为1。nums[i]能否作为1要看右边可行的3 2组合，
    为了判断这一点，倒序遍历的过程中，记录存在的3 2组合的2最大能多大，这样就能让nums[i]尽量能成为1。
    如何记录可行的3 2组合？单调栈，nums[i]若不能成为1，则尝试作为3更新3 2组合，nums[i]作为3让栈中 < 自己的出栈，
    直到栈顶>=nums[i]。
    有没有可能栈顶右边还有更大的2？
    注意栈顶>=nums[i]，再往右，当前nums[i]已经不能作为3了，那种会在前面被枚举
    */
    bool find132pattern_implementation2(vector<int>& nums) {
        int n = nums.size();
        int max_of_2 = INT_MIN;
        stack<int> st; // 从左到右单增
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] < max_of_2) return true;
            while (!st.empty() && nums[st.top()] < nums[i]) { // nums[i]作为3
                max_of_2 = nums[st.top()]; // 这里没求max
                st.pop();
            }
            if (nums[i] > max_of_2) st.push(i); // > max_of_2 才进单调栈
        }
        return false;
    }

    // 官方题解解法二的另外一种写法，更寻常的单调栈写法
    bool find132pattern_implementation3(vector<int>& nums) {
        int n = nums.size();
        int max_of_2 = INT_MIN;
        stack<int> st; // 从左到右单增
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] < max_of_2) return true;
            while (!st.empty() && nums[st.top()] < nums[i]) { // nums[i]作为3
                max_of_2 = max(max_of_2, nums[st.top()]);
                st.pop();
            }
            st.push(i);
        }
        return false;
    }

    /* 官方题解评论区的一种枚举2的解法，时间复杂度O(n)，这种方法可以用于nums以流式给出的情况
    枚举2，用单调栈记录左边离2最近的>2的值，然后看前缀最小值是否 < 2
    <https://leetcode.cn/problems/132-pattern/solutions/676437/132mo-shi-by-leetcode-solution-ye89/comments/850676/>
    */
    bool find132pattern_implementation4(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre_min(n + 1, INT_MAX);
        for (int i = 0; i < n; i++) {
            pre_min[i + 1] = min(pre_min[i], nums[i]);
        }

        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            if (!st.empty() && pre_min[st.top() - 1 + 1] < nums[i]) return true;
            st.push(i);
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution456 solu;
    cout << solu.find132pattern(*new vector<int>{1,2,3,4}) << endl;
    cout << solu.find132pattern(*new vector<int>{3,1,4,2}) << endl;

    cout << solu.find132pattern_implementation2(*new vector<int>{1,2,3,4}) << endl;
    cout << solu.find132pattern_implementation2(*new vector<int>{3,1,4,2}) << endl;

    cout << solu.find132pattern_implementation3(*new vector<int>{1,2,3,4}) << endl;
    cout << solu.find132pattern_implementation3(*new vector<int>{3,1,4,2}) << endl;
    return 0;
}
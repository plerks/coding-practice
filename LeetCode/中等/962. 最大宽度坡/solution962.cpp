/*
url: https://leetcode.cn/problems/maximum-width-ramp/
参考: https://leetcode.cn/problems/maximum-width-ramp/solutions/243679/java-dan-diao-zhan-er-fen-jie-fa-chang-shi-jie-shi/
相关: LeetCode503. 下一个更大元素 II, LeetCode1124. 表现良好的最长时间段
标签: 【算法题单】单调栈, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution962 {
public:
    /* 参考题解，寻找最大的j - i，使得(i, j)的nums[i] <= nums[j]，
    考虑从nums[0]开始的单减序列，最优解的i一定在这个序列中，否则若i在更左且不在这个序列中，
    则若nums[i_ans]比左右的隔板更大，则i取0一定最优；若更小，则其应该在此序列中。
    然后从右往左枚举j即可。
    时间复杂度O(n)

    这个问题情景很像LeetCode503 nextGreaterElements_wrong()，如果能求出 每个j左侧最远的小于自己的i 就好了，
    但是这个方法只对这题的情景求最大距离有效，不能用来求每个j左侧最远的小于自己的i，例如最优解为(0, n - 1)，一下栈就空了。
    */
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        stack<int> st; // 求nums[0]开始的单减序列
        for (int i = 0; i < n; i++) { // 这里求的是单减序列，但是不是单调栈的写法
            if (st.empty() || nums[st.top()] > nums[i]) st.push(i);
        }
        for (int j = n - 1; j >= 0; j--) { // 从右往左枚举
            if (st.empty()) break;
            while (!st.empty() && nums[st.top()] <= nums[j]) { // 这里也不是单调栈的写法
                ans = max(ans, j - st.top());
                st.pop(); // 以后就算能用，距离也更小，所以pop
            }
        }
        return ans;
    }

    // 参考题解还有个解法二，找出nums[0]开始的单减序列后，既然最优解的i一定在这个序列中，则枚举j，二分查找第一个<=j的位置i，不过时间复杂度要O(nlogn)
};

int main(int argc, char const *argv[]) {
    Solution962 solu;
    cout << solu.maxWidthRamp(*new vector<int>{6,0,8,2,1,5}) << endl;
    return 0;
}
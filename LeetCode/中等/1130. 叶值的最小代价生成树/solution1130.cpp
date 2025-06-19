/*
url: https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/
参考: https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/solutions/2285433/xie-zhi-de-zui-xiao-dai-jie-sheng-cheng-26ozf/
      https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/solutions/377595/wei-shi-yao-dan-diao-di-jian-zhan-de-suan-fa-ke-xi/
标签: 【算法题单】单调栈, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1130 {
public:
    /* 参考题解，能想到huffman树，但是这题不能随便动arr的相对顺序，然后不知道怎么操作。
    用[6,2,4]和[6,2,8]这两个用例来看，2需要暂存，然后遇到8的时候，决定2和6还是8乘，然后由于算内部节点的值时取叶节点的最大值，
    2就不会产生作用了，栈中为6和8。
    要把大的值尽量放在更高的地方，小的值放在低的地方，才能得到最小总和。
    栈是单减的，遇到 V 形的3个数，就需要计算了，栈最底部相当于有个INT_MAX
    */
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        stack<int> st; // 栈单减
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.top() <= arr[i]) {
                int small = st.top(); // 一个极小值
                st.pop();
                int other = min(arr[i], st.empty() ? INT_MAX : st.top());
                ans += small * other;
            }
            st.push(arr[i]); // V 形的3个数，不管极小值和哪个结合，最终都是两个较大的两个数留下来
        }

        // 栈中还有剩余元素。现在相当于有个INT_MAX要入栈
        while (st.size() >= 2) {
            int small = st.top();
            st.pop();
            ans += small * st.top();
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1130 solu;
    cout << solu.mctFromLeafValues(*new vector<int>{6,2,4}) << endl;
    return 0;
}
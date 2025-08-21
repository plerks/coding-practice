/*
url: https://leetcode.cn/problems/longest-valid-parentheses/
参考: https://leetcode.cn/problems/longest-valid-parentheses/solutions/314683/zui-chang-you-xiao-gua-hao-by-leetcode-solution/
标签: 括号匹配
*/

#include <bits/stdc++.h>

using namespace std;

class Solution32 {
public:
    /* 官方题解解法一，dp
    考虑求以s[i]结尾的最长合法子串，其必须是)，如果是'('的话dp[i]为0
    只需考虑s[i] == ')'的情况，考虑dp[i]的计算，
    如果s[i - 1]为'('，则 dp[i] = dp[i - 2] + 2，
    如果s[i - 1]为')'，一个合法的括号匹配，各个符号的配对方式一定唯一，所以考虑 s[i - 1] 的合法串[i - dp[i - 1] , i - 1] （也可能
    s[i - 1]没有合法串，此时dp[i - 1]为0 ），然后 s[i - dp[i - 1] - 1] 必须得是‘(’和s[i]匹配，然后再加上前面的最大合法长度，即：
        dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2]
    */
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n + 1); // dp数组偏移1，虽然上面有dp[i - 2]这样的，但是下标最小为-1，只偏移1就够
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') continue;
            if (i - 1 < 0) continue; // dp[0] 一定为 0
            if (s[i - 1] == '(') dp[i + 1] = dp[i - 2 + 1] + 2;
            else {
                if (i - dp[i - 1 + 1] - 1 >= 0 && s[i - dp[i - 1 + 1] - 1] == '(') {
                    dp[i + 1] = dp[i - 1 + 1] + 2 + dp[i - dp[i - 1 + 1] - 2 + 1];
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    /* 官方题解解法二，这两个解法有点像最大子数组和的dp解法和单纯一次遍历解法，
    当我们遍历到 i 位置的 ')' 时，考虑以 i 结尾的最长合法匹配。栈中如果有一个 '(' 可以与之匹配，那么我们只需考虑往左最远能到多远，
    上一次多出来的')'会隔断，让栈底记录“最后一个没有被匹配的右括号的下标”， (这个下标, i] 就是以 i 结尾的最长匹配。
    */
    int longestValidParentheses_implementation2(string s) {
        int n = s.size();
        int ans = 0;
        stack<int> st;
        st.push(-1); // 虚拟s[-1] = ')'
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push(i);
            else {
                st.pop(); // 这里可能把 s[-1] 当 '(' 用，但是没事，这样之后马上栈为空，i 马上就会作为隔断
                if (st.empty()) { // 无法匹配
                    st.push(i);
                }
                else {
                    ans = max(ans, i - st.top());
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution32 solu;
    cout << solu.longestValidParentheses(")()())") << endl;
    cout << solu.longestValidParentheses("()(())") << endl;

    cout << solu.longestValidParentheses_implementation2(")()())") << endl;
    return 0;
}
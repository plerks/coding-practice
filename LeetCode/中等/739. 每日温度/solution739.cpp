/*
url: https://leetcode.cn/problems/daily-temperatures/
标签: 【算法题单】单调栈, [mark]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution739 {
public:
    // i让左侧所有小于自己的j出栈，从而知道ans[j]
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    // 换一个方向遍历，i让右侧所有小于等于自己的j出栈，从而知道ans[i]
    vector<int> dailyTemperatures_implementation2(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && temperatures[st.top()] <= temperatures[i]) {
                st.pop();
            }
            ans[i] = st.empty() ? 0 : st.top() - i;
            st.push(i);
        }
        return ans;
    }

    // 这里单调栈的填自己和填别人，有点像dp的填表法与刷表法
};

int main(int argc, char const *argv[]) {
    Solution739 solu;
    auto a = solu.dailyTemperatures(*new vector<int>{73,74,75,71,69,72,76,73});

    auto b = solu.dailyTemperatures_implementation2(*new vector<int>{73,74,75,71,69,72,76,73});
    return 0;
}
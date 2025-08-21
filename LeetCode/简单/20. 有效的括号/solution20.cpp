// https://leetcode.cn/problems/valid-parentheses/

#include <bits/stdc++.h>

using namespace std;

class Solution20 {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            }
            else {
                if (c == ')' && (st.empty() || st.top() != '(')) return false;
                if (c == ']' && (st.empty() || st.top() != '[')) return false;
                if (c == '}' && (st.empty() || st.top() != '{')) return false;
                st.pop();
            }
        }
        return st.empty();
    }
};

int main(int argc, char const *argv[]) {
    Solution20 solu;
    cout << solu.isValid("([])") << endl;
    return 0;
}
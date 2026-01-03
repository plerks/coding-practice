/*
url: https://leetcode.cn/problems/remove-invalid-parentheses/
参考: https://leetcode.cn/problems/remove-invalid-parentheses/solutions/1067271/shan-chu-wu-xiao-de-gua-hao-by-leetcode-9w8au/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution301 {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> ans;
        if (isValid(s)) return { s };

        auto bfs = [&]() {
            queue<string> q;
            unordered_set<string> vis;
            q.push(s);
            vis.insert(s);
            int level = 1;
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; i++) {
                    string cur = q.front(); q.pop();
                    for (int i = 0; i < cur.size(); i++) {
                        string next = cur;
                        if (next[i] == '(' || next[i] == ')') next.erase(next.begin() + i);
                        if (isValid(next)) {
                            ans.insert(next);
                        }
                        if (!vis.count(next)) q.push(next), vis.insert(next);
                    }
                }
                if (!ans.empty()) return;
                level++;
            }
        };

        bfs();

        vector<string> ans_vec(ans.begin(), ans.end());

        return ans_vec;
    }

    // 参考官方题解，判断合法不需要用栈，直接从左到右遍历，记录 '(' 和 ')' 的 diff 就可以
    bool isValid(string& s) {
        int diff = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') diff++;
            else if (s[i] == ')') {
                diff--;
                if (diff < 0) return false;
            }
        }
        return diff == 0;
    }
};

int main(int argc, char const *argv[]) {
    Solution301 solu;
    auto a = solu.removeInvalidParentheses("()())()");
    auto b = solu.removeInvalidParentheses("(a)())()");
    return 0;
}
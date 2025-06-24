/*
url: https://leetcode.cn/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/
相关: LeetCode1673. 找出最具竞争力的子序列
标签: 【算法题单】单调栈, 字典序
*/
#include <bits/stdc++.h>

using namespace std;

// 这题相当于在LeetCode1673的基础上加上了个要保留至少repetition个letter的限制
// 那就意味着其它字符最多 k - repetition 个
class Solution2030 {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.size();
        int cnt = 0; // 栈和s剩余部分的letter个数
        for (char c : s) cnt += c == letter;
        vector<char> st;
        int cur = 0; // 栈中letter的个数
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back() > s[i] && st.size() - 1 + n - i >= k) { // 要能有k个字符
                if (st.back() == letter && cnt - 1 < repetition) { // letter不能删光了
                    break;
                }
                cur -= st.back() == letter;
                cnt -= st.back() == letter;
                st.pop_back();
            }
            if (st.size() == k) {
                cnt -= s[i] == letter;
                continue;
            }
            if (s[i] != letter) {
                // 其它字符最多 k - repetition 个
                if (st.size() + 1 - cur <= k - repetition) st.push_back(s[i]);
            }
            else {
                st.push_back(s[i]);
                cur++;
            }
        }

        string ans;
        for (char c : st) {
            ans.push_back(c);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2030 solu;
    // cout << solu.smallestSubsequence("leet", 3, 'e', 1) << endl;
    // cout << solu.smallestSubsequence("leetcode", 4, 'e', 2) << endl;
    // cout << solu.smallestSubsequence("aaabbbcccddd", 3, 'b', 2) << endl;
    // cout << solu.smallestSubsequence("adffhjfmmmmorsfff", 6, 'f', 5) << endl;
    // cout << solu.smallestSubsequence("bba", 1, 'b', 1) << endl;
    cout << solu.smallestSubsequence("cabceccefbbcebfbeaf", 4, 'c', 1) << endl;
    return 0;
}
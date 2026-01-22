/*
url: https://leetcode.cn/problems/lexicographically-smallest-string-after-deleting-duplicate-characters/
参考: https://leetcode.cn/problems/lexicographically-smallest-string-after-deleting-duplicate-characters/solutions/3883318/dan-diao-zhan-pythonjavacgo-by-endlessch-48tm/
相关: LeetCode316. 去除重复字母
标签: LeetCode第485场周赛
*/

// 这次周赛两题，第二题最后几分钟调出来的

#include <bits/stdc++.h>

using namespace std;

class Solution3816 {
public:
    // 参考灵茶题解，单调栈，与LeetCode316基本一致
    string lexSmallestAfterDeletion(string s) {
        int n = s.size();
        vector<char> st;
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a']++;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back() > s[i] && cnt[st.back() - 'a'] > 1) {
                char out = st.back();
                st.pop_back();
                cnt[out - 'a']--;
            }
            st.push_back(s[i]);
        }
        // 对末尾还要做一次
        while (!st.empty() && cnt[st.back() - 'a'] > 1) {
            char out = st.back();
            st.pop_back();
            cnt[out - 'a']--;
        }
        string ans;
        std::for_each(st.begin(), st.end(), [&](char &c) {
            ans.push_back(c);
        });
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3816 solu;
    // cout << solu.lexSmallestAfterDeletion("bcabc") << endl;
    // cout << solu.lexSmallestAfterDeletion("cbacdcbc") << endl;
    cout << solu.lexSmallestAfterDeletion("cdadabcc") << endl;
    return 0;
}
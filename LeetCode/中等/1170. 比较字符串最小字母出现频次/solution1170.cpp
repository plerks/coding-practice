/*
url: https://leetcode.cn/problems/compare-strings-by-frequency-of-the-smallest-character/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1170 {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> w(words.size());

        auto f = [&](string &s) {
            int cnt[26]{};
            for (char c : s) cnt[c - 'a']++;
            for (int x : cnt) if (x != 0) return x;
            return -1;
        };

        for (int i = 0; i < words.size(); i++) {
            w[i] = f(words[i]);
        }
        sort(w.begin(), w.end());

        vector<int> ans(queries.size());

        for (int i = 0; i < queries.size(); i++) {
            string &q = queries[i];
            int fs = f(q);
            // 第一个大于fs
            int cnt = w.end() - upper_bound(w.begin(), w.end(), fs);
            ans[i] = cnt;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1170 solu;
    auto a = solu.numSmallerByFrequency(*new vector<string>{"bbb","cc"}, *new vector<string>{"a","aa","aaa","aaaa"});
    return 0;
}
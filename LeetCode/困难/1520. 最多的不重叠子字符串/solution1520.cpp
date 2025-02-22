/*
url: https://leetcode.cn/problems/maximum-number-of-non-overlapping-substrings/
相关: LeetCode3458. 选择 K 个互不重叠的特殊子字符串
*/

// 此题与`LeetCode3458. 选择 K 个互不重叠的特殊子字符串`几乎完全相同

#include <bits/stdc++.h>

using namespace std;

class Solution1520 {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        int posL[26]{};
        std::fill(std::begin(posL), std::end(posL), -1);
        int posR[26]{};
        std::fill(std::begin(posR), std::end(posR), -1);
        for (int i = 0; i < n; i++) {
            if (posL[s[i] - 'a'] == -1) posL[s[i] - 'a'] = i;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (posR[s[i] - 'a'] == -1) posR[s[i] - 'a'] = i;
        }

        vector<pair<int, int>> legals;

        for (int i = 0; i < 26; i++) { // 枚举字母
            if (posL[i] != -1) { // s存在这个字母
                int l = posL[i];
                int r = posR[i];
                int tl = l, tr = r;
                for (int i = tl + 1; i < tr; i++) {
                    l = min(l, posL[s[i] - 'a']);
                    r = max(r, posR[s[i] - 'a']);
                }
                // 这里对于为了使串合法而可能需要往左右扩展我是这样写的，是正确的，能正确处理不断会引入新字符的多变性
                while (l < tl || tr < r) {
                    while (tl > l) {
                        l = min(l, posL[s[tl] - 'a']);
                        r = max(r, posR[s[tl] - 'a']);
                        tl--;
                    }
                    while (tr < r) {
                        l = min(l, posL[s[tr] - 'a']);
                        r = max(r, posR[s[tr] - 'a']);
                        tr++;
                    }
                }
                legals.push_back({l, r});
            }
        }

        // 上面得到的区间最多26个，但是是可能有重叠的，比如eaafaag，会得到aafaa和f这两个有重叠的区间
        // LeetCode435. 无重叠区间，求最多能取出的无重叠区间
        sort(legals.begin(), legals.end(), [](pair<int, int> &x, pair<int, int> &y) {
            return x.second < y.second;
        });

        vector<string> ans;
        int edge = INT_MIN;
        for (auto &[l, r] : legals) {
            if (l > edge) {
                ans.push_back(s.substr(l, r - l + 1));
                edge = r;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1520 solu;
    auto a = solu.maxNumOfSubstrings("adefaddaccc");
    auto b = solu.maxNumOfSubstrings("abab");
    return 0;
}
/*
url: https://leetcode.cn/problems/select-k-disjoint-special-substrings/
参考: https://www.bilibili.com/video/BV1pmAGegEcw/
      https://leetcode.cn/problems/select-k-disjoint-special-substrings/solutions/3077261/you-xiang-tu-jian-mo-he-bing-qu-jian-bu-sw1lb/
相关: LeetCode435. 无重叠区间, LeetCode1520. 最多的不重叠子字符串
标签: LeetCode第437场周赛
*/

// 此题与`LeetCode1520. 最多的不重叠子字符串`几乎完全相同

#include <bits/stdc++.h>

using namespace std;

class Solution3458 {
public:
    /* 周赛时的想法，虽然过了很多用例（978 / 989 个通过的测试用例），不过还是wa了，应该策略有问题，
    想法是：要获得最大的切片数量，如果一次字符只出现一次，那其应该单独作为一片；若出现不止一次，则其
    应当尽量扩展，使其它的自己也在同一个切片中，这样自己就是合法的了，不过如果中途遇到了只出现一次的
    字符，则应停止扩展，让单字符自成一片。
    然后切出subs后，检查其中合法的子串(例如subs = ["ab", "c", "ab"]，那么ab不合法)，看数量是否>=k。
    但是对["zhqzqqcpamgiykmcozsphnnqtebbetwtwtbfrucxgcmpshiuus", 8]这个用例wa了，
    这个用例看不出来为什么，但是我想出来了原因，以下代码对["aabb", 2]会返回false，但是实际应该返回true，
    也就是说，原本a和b都是出现次数>1，但是他们可以分别拆成2片，而不是一片。我的代码没有判断是否要把子串延展
    那么长，像"aabb"，到a结束就不用延展了，而像"abab"这种"你中有我，我中有你"的情况，就需要完全的延展。
    (LeetCode这用例有点弱，居然到了900多个用例才查出来["aabb", 2]这种错)
    */
    bool maxSubstringLength_wa(string s, int k) {
        int n = s.size();
        unordered_map<char, int> map;
        for (char ch : s) map[ch]++;
        vector<string> subs;
        for (int i = 0; i < n;) {
            unordered_set<char> seen;
            int start = i;
            if (map[s[start]] == 1) {
                subs.push_back(s.substr(start, 1));
                i = start + 1;
                continue;
            }
            i++;
            while (i < n && map[s[i]] >= 2) {
                seen.insert(s[i]);
                i++;
            }
            subs.push_back(s.substr(start, i - start));
        }
        int counter[26]{};
        for (string &s : subs) {
            int cnt[26]{};
            for (char ch : s) {
                if (cnt[ch - 'a'] == 0) cnt[ch - 'a'] = 1;
            }
            for (int i = 0; i < 26; i++) counter[i] += cnt[i];
        }
        
        int ans = 0;
        for (string &s : subs) {
            bool legal = true;
            for (char ch : s) {
                if (counter[ch - 'a'] > 1) {
                    legal = false;
                    break;
                }
            }
            if (legal) ans++;
        }
        return ans >= k;
    }

    /* 参考灵茶题解，
    找出所有极小合法串，假如一个合法串需要包含a，则其需要包含所有的a，且也要包含这之中的所有其它字符，
    所以，记录每个字母出现的最左右位置，枚举合法串包含的字母。
    找出所有合法串之后，用LeetCode435. 无重叠区间，找出能选出的无重叠的区间的最大个数。
    对于合法串的繁复扩展，采用记每个字母出现的最左右位置并模拟向左向右扩展的方式。时间复杂度O(26n)
    */
    bool maxSubstringLength(string s, int k) {
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

        int edge = INT_MIN;
        int cnt = 0;
        for (auto &[l, r] : legals) {
            if (l == 0 && r == n - 1) continue; // 题目要求不能用s这个串本身
            if (l > edge) {
                cnt++;
                edge = r;
            }
        }
        return cnt >= k;
    }

    /* 原本的灵茶题解中对于合法串的扩展用了如下这种有点复杂但很特别的方式，把26个字母组成图，
    假如 a...a 中间含有b，则 a -> b 应有一条有向边，这代表如果合法串要含有a，那么根据图要继续查，
    要让串也含有b。这样就能看出构建的图是有什么用了。
    如何判断 a...a 中间有没有b？
    记录每个字母的所有出现位置，二分查找b在a的第一个出现位置右边的第一个出现位置，判断是否在a的最右出现位置的左边，就知道
    a有没有夹b了。最后比如考虑串要包含a，则问题变成 串包含a -> 串要包含所有a -> 根据有向图，串要包含所有b -> 根据有向图，串要包含所有c ...
    时间复杂度O(n + 26 * 26 * logn)，相比maxSubstringLength()时间复杂度确实更低，很神奇！
    */
    bool maxSubstringLength_implementation2(string s, int k) {
        int n = s.size();
        vector<vector<int>> pos(26);
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'].push_back(i);
        }

        vector<vector<int>> g(26); // 图

        for (int i = 0; i < 26; i++) { // 构建图的边关系
            if (!pos[i].empty()) {
                int l = pos[i].front();
                int r = pos[i].back();
                for (int j = 0; j < 26; j++) {
                    if (i == j) continue;
                    // 找j的第一个>l的出现位置
                    int index = upper_bound(pos[j].begin(), pos[j].end(), l) - pos[j].begin();
                    if (index != pos[j].size() && pos[j][index] < r) {
                        // 要包含所有i，就得引入j
                        g[i].push_back(j);
                    }
                }
            }
        }

        vector<pair<int, int>> legals;
        auto dfs = [&](auto &dfs, int ch, int &l, int &r, bool* visited) -> void { // 注意l r传的引用
            if (visited[ch]) return;
            visited[ch] = true;
            l = min(l, pos[ch].front());
            r = max(r, pos[ch].back());
            for (int next : g[ch]) {
                dfs(dfs, next, l, r, visited);
            }
        };
        for (int i = 0; i < 26; i++) { // 枚举字母
            if (!pos[i].empty()) {
                bool visited[26]{};
                int l = pos[i].front();
                int r = pos[i].back();
                dfs(dfs, i, l, r, visited); // dfs求最终区间
                legals.push_back({l, r});
            }
        }

        // 上面得到的区间最多26个，但是是可能有重叠的，比如eaafaag，会得到aafaa和f这两个有重叠的区间
        // LeetCode435. 无重叠区间，求最多能取出的无重叠区间
        sort(legals.begin(), legals.end(), [](pair<int, int> &x, pair<int, int> &y) {
            return x.second < y.second;
        });

        int edge = INT_MIN;
        int cnt = 0;
        for (auto &[l, r] : legals) {
            if (l == 0 && r == n - 1) continue; // 题目要求不能用s这个串本身
            if (l > edge) {
                cnt++;
                edge = r;
            }
        }
        return cnt >= k;
    }
};

int main(int argc, char const *argv[]) {
    Solution3458 solu;
    cout << solu.maxSubstringLength("abcdbaefab", 2) << endl;
    cout << solu.maxSubstringLength("aabb", 2) << endl;
    cout << solu.maxSubstringLength("cbcaba", 1) << endl;

    cout << solu.maxSubstringLength_implementation2("abcdbaefab", 2) << endl;
    cout << solu.maxSubstringLength_implementation2("aabb", 2) << endl;
    cout << solu.maxSubstringLength_implementation2("cbcaba", 1) << endl;
    return 0;
}

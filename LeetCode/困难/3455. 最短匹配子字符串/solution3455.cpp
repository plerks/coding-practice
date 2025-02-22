/*
url: https://leetcode.cn/problems/shortest-matching-substring/
参考: https://leetcode.cn/problems/shortest-matching-substring/solutions/3076453/xian-xing-zuo-fa-kmpmei-ju-zhong-jian-sa-5qow/
标签: LeetCode第150场双周赛, kmp, 二分, 三指针
*/

// 这次双周赛2题

#include <bits/stdc++.h>

using namespace std;

class Solution3455 {
public:
    vector<int> buildOptimizedNext(string& p) {
        int n = p.size();
        vector<int> next(n + 1);
        next[0] = -1;
        int j = 0, t = -1;
        while (j < n) { // 要寻找所有匹配位置，这里j范围要大1，把next[n]也算出来
            // 现在t为非改进next[j]，目标：求出非改进next[j + 1]，再求出改进next[j + 1]
            while (t >= 0 && p[j] != p[t]) t = next[t];
            next[j + 1] = (p[j + 1] != p[t + 1]) ? t + 1 : next[t + 1];
            j++;
            t++;
        }
        return next;
    }

    // 在s中找出p的所有出现位置
    vector<int> kmp_all_matches(string& s, string p) {
        if (p.size() == 0) {
            vector<int> matches(s.size() + 1);
            iota(matches.begin(), matches.end(), 0);
            return matches;
        }
        vector<int> next = buildOptimizedNext(p);
        vector<int> matches;
        int i = 0, j = 0;
        int m = s.size();
        int n = p.size();
        while (i < m) {
            while (j >= 0 && s[i] != p[j]) j = next[j];
            i++;
            j++;
            if (j == n) {
                matches.push_back(i - j);
                j = next[j]; // p[n]没有字符，相当于在n处失配，j变为next[n]
            }
        }
        return matches;
    }

    // 参考灵茶题解，用二分来写，时间复杂度O(m + n + mlogm)
    int shortestMatchingSubstring(string s, string p) {
        // split，这里题目*只有2个，可以直接手写把p给split，但是split也需要用找所有出现位置来实现，所以这样写：
        vector<int> posstar = kmp_all_matches(p, "*");
        posstar.insert(posstar.begin(), -1);
        posstar.push_back(p.size());
        vector<string> split;
        for (int i = 0; i < posstar.size() - 1; i++) {
            split.push_back(p.substr(posstar[i] + 1, posstar[i + 1] - posstar[i] - 1));
        }

        int size1 = split[0].size(), size2 = split[1].size(), size3 = split[2].size();
        // 所有出现位置
        vector<int> pos1 = kmp_all_matches(s, split[0]);
        vector<int> pos2 = kmp_all_matches(s, split[1]);
        vector<int> pos3 = kmp_all_matches(s, split[2]);

        int ans = INT_MAX;

        // 三段，枚举中间，然后二分两边。也可以枚举左，二分中和右
        for (int p2 : pos2) {
            // 搜索pos1里最后一个p1 + size1 <= p2
            int p1 = upper_bound(pos1.begin(), pos1.end(), p2 - size1) - pos1.begin();
            p1--;
            // 搜索pos3里第一个p2 + size2 <= p3
            int p3 = lower_bound(pos3.begin(), pos3.end(), p2 + size2) - pos3.begin();
            if (p1 != -1 && p3 != pos3.size()) ans = min(ans, pos3[p3] + size3 - pos1[p1]);
        }
        return ans == INT_MAX ? -1 : ans;
    }

    // 参考灵茶题解，用三指针来写，时间复杂度O(m + n + mlogm)
    int shortestMatchingSubstring_implementation2(string s, string p) {
        // split，这里题目*只有2个，可以直接手写把p给split，但是split也需要用找所有出现位置来实现，所以这样写：
        vector<int> posstar = kmp_all_matches(p, "*");
        posstar.insert(posstar.begin(), -1);
        posstar.push_back(p.size());
        vector<string> split;
        for (int i = 0; i < posstar.size() - 1; i++) {
            split.push_back(p.substr(posstar[i] + 1, posstar[i + 1] - posstar[i] - 1));
        }

        int size1 = split[0].size(), size2 = split[1].size(), size3 = split[2].size();
        // 所有出现位置
        vector<int> pos1 = kmp_all_matches(s, split[0]);
        vector<int> pos2 = kmp_all_matches(s, split[1]);
        vector<int> pos3 = kmp_all_matches(s, split[2]);

        int ans = INT_MAX;
        int l = 0, r = 0;
        // 三段，枚举中间
        for (int m : pos2) {
            // 找第一个>的，或者让l初值为-1，然后检查l+1合法的话就l++
            while (l < pos1.size() && pos1[l] + size1 <= m) l++;
            while (r < pos3.size() && m + size2 > pos3[r]) r++;
            if (r == pos3.size()) break;
            if (l > 0) ans = min(ans, pos3[r] + size3 - pos1[l - 1]);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3455 solu;
    cout << solu.shortestMatchingSubstring("abaacbaecebce", "ba*c*ce") << endl;
    cout << solu.shortestMatchingSubstring_implementation2("abaacbaecebce", "ba*c*ce") << endl;
    return 0;
}
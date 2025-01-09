/*
url: https://leetcode.cn/problems/substring-matching-pattern/description/
参考: https://leetcode.cn/problems/substring-matching-pattern/solutions/3038944/ku-han-shu-jian-ji-xie-fa-pythonjavacgo-sukdf/
标签: LeetCode第147场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3407 {
public:
    // 周赛时的写法，通过
    bool hasMatch(string s, string p) {
        int n = s.size();
        // int m = p.size();
        int pos = p.find("*");
        string sub1 = p.substr(0, pos);
        int len1 = pos;
        string sub2 = p.substr(pos + 1);
        // int len2 = m - (pos + 1);
        for (int i = 0; i < n; i++) {
            if (s.substr(i, len1) == sub1 && s.find(sub2, i + len1) != string::npos) {
                return true;
            }
        }
        return false;
    }

    // 灵茶山艾府写法，更简洁
    bool hasMatch_implementation2(string s, string p) {
        int pos1 = p.find('*');
        string first = p.substr(0, pos1 - 0);
        int pos2 = s.find(first);
        return pos2 != string::npos && s.find(p.substr(pos1 + 1), pos2 + pos1) != string::npos;
    }
};

int main(int argc, char const *argv[]) {
    Solution3407 solu;
    cout << solu.hasMatch("leetcode", "ee*e") << endl;
    cout << solu.hasMatch_implementation2("leetcode", "ee*e") << endl;
    return 0;
}
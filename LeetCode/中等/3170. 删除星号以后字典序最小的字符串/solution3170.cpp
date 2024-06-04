/*
url: https://leetcode.cn/problems/lexicographically-minimum-string-after-removing-stars/description/
标签: LeetCode第400场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3170 {
public:
    // 周赛时的解法，通过。也可以用26个栈。
    string clearStars(string s) {
        int n = s.size();
        auto comparator = [](pair<char, int> &x, pair<char, int> &y) {
            if (x.first != y.first) return x.first > y.first;
            if (x.second != y.second) return x.second < y.second;
            return false;
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(comparator)> pq(comparator);
        vector<bool> deleteMap(n, 0);
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (ch != '*') {
                pq.push(make_pair(ch, i));
            }
            else {
                deleteMap[i] = 1;
                if (pq.empty()) continue;
                auto& p = pq.top();
                deleteMap[p.second] = 1;
                pq.pop();
            }
        }
        string ans;
        for (int i = 0; i < n; i++) {
            if (deleteMap[i] == 0) ans += s[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3170 solu;
    cout << solu.clearStars("aaba*") << endl;
    return 0;
}

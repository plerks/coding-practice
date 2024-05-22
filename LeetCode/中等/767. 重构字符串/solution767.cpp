/*
url: https://leetcode.cn/problems/reorganize-string/description/
相关: LeetCode1953. 你可以工作的最大周数, LeetCode1054. 距离相等的条形码
标签: 构造
*/

#include <bits/stdc++.h>

using namespace std;

// 此题与`LeetCode1054. 距离相等的条形码`相同
class Solution767 {
public:
    string reorganizeString(string s) {
        int n = s.size();
        map<char, int> map; // [char, 频率]
        for (char ch : s) {
            map[ch]++;
        }
        vector<pair<int, char>> v;
        for (auto it = map.begin(); it != map.end(); it++) {
            v.push_back(make_pair(it->second, it->first)); // [频率, char]
        }
        sort(v.begin(), v.end(), greater<pair<int, char>>());
        if (v[0].first > (n - v[0].first) + 1) return "";
        string ans(n, '0');
        int evenIndex = 0;
        int oddIndex = 1;
        for (auto &p : v) {
            int freq = p.first;
            char ch = p.second;
            while (freq > 0) {
                if (evenIndex < n) {
                    ans[evenIndex] = ch;
                    evenIndex += 2;
                }
                else {
                    ans[oddIndex] = ch;
                    oddIndex += 2;
                }
                freq--;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution767 solu;
    cout << solu.reorganizeString("aab") << endl;
    return 0;
}

/*
url: https://leetcode.cn/problems/naming-a-company/description/?envType=daily-question&envId=2024-09-25
LeetCode参考: https://leetcode.cn/problems/naming-a-company/solutions/1596320/by-endlesscheng-ruz8/
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2306 {
public:
    // 超时，76 / 89 个通过的测试用例
    long long distinctNames_time_limit_exceeded(vector<string>& ideas) {
        unordered_map<string, unordered_set<char>> map; // map[s]表示以s作为后缀的字符串，有哪些首字母
        for (const string &s : ideas) {
            map[s.substr(1)].insert(s[0]);
        }
        long long ans = 0;
        for (auto &[s1, set1] : map) {
            for (auto &[s2, set2] : map) {
                if (s1 == s2) continue;
                for (char c1 : set1) {
                    for (char c2 : set2) {
                        if (!set2.count(c1) && !set1.count(c2)) {
                            ans++;
                        }
                    }
                }
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法一
    long long distinctNames(vector<string>& ideas) {
        unordered_set<string> group[26]; // 按首字母分组
        for (const string &s : ideas) {
            group[s[0] - 'a'].insert(s.substr(1));
        }

        long long ans = 0;

        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j < 26; j++) {
                // i,j对应的set中的元素交换不合法 当且仅当 元素在二者的交集中
                int m = 0; // 交集元素个数
                for (const string &s : group[j]) {
                    if (group[i].count(s)) m++;
                }
                ans += (long long)(group[i].size() - m) * (group[j].size() - m);
            }
        }
        return ans * 2; // 最后乘2，两个word能交换一次
    }

    // 灵茶山艾府题解解法二
    // 题目的关键在于计算后缀的交集大小，所以在遍历过程中记录每个后缀有哪些首字母
    long long distinctNames_implementation2(vector<string>& ideas) {
        int size[26]{}; // 各字母开头的元素个数
        int intersection[26][26]{}; // intersection[i][j]表示i, j开头的字母的后缀的交集大小
        unordered_map<string, int> map; // map[s]表示以s作为后缀的字符串，有哪些首字母，用一个int存有哪些首字母
        for (auto s : ideas) {
            size[s[0] - 'a']++;
            string suffix = s.substr(1);
            for (int i = 0; i < 26; i++) {
                if (map[suffix] >> i & 1) {
                    intersection[s[0] - 'a'][i]++;
                    intersection[i][s[0] - 'a']++;
                }
            }
            map[suffix] |= 1 << s[0] - 'a';
        }
        long long ans = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j < 26; j++) {
                int m = intersection[i][j];
                ans += (long long)(size[i] - m) * (size[j] - m);
            }
        }
        return ans * 2;
    }
};

int main(int argc, char const *argv[]) {
    Solution2306 solu;
    vector<string> ideas = {"coffee","donuts","time","toffee"};
    cout << solu.distinctNames(ideas) << endl;
    cout << solu.distinctNames_implementation2(ideas) << endl;
    return 0;
}

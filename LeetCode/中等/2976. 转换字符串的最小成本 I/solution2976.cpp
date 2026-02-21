/*
url: https://leetcode.cn/problems/minimum-cost-to-convert-string-i/
标签: Floyd
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2976 {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        long long d[26][26];
        const long long inf = INT64_MAX / 2;
        fill(&d[0][0], &d[0][0] + sizeof(d) / sizeof(long long), inf);
        for (int i = 0; i < 26; i++) d[i][i] = 0;
        for (int i = 0; i < original.size(); i++) {
            char u = original[i], v = changed[i];
            d[u - 'a'][v - 'a'] = min(d[u - 'a'][v - 'a'], (long long)cost[i]); // 有重边
        }
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (d[i][k] != inf && d[k][j] != inf && d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < source.size(); i++) {
            long long dis = d[source[i] - 'a'][target[i] - 'a'];
            if (dis == inf) return -1;
            ans += dis;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2976 solu;
    cout << solu.minimumCost("abcd", "acbe", *new vector<char>{'a','b','c','c','e','d'}, *new vector<char>{'b','c','b','e','b','e'}, *new vector<int>{2,5,5,1,2,20}) << endl;
    return 0;
}
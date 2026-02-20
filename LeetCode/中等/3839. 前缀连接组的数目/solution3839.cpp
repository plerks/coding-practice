/*
url: https://leetcode.cn/problems/number-of-prefix-connected-groups/
标签: LeetCode第176场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3839 {
public:
    int prefixConnected(vector<string>& words, int k) {
        unordered_map<string, int> mp;
        for (string& word : words) {
            if (word.size() < k) continue;
            mp[word.substr(0, k)]++;
        }
        int ans = 0;
        for (auto &[s, freq] : mp) {
            if (freq >= 2) ans++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
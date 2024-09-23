/*
url: https://leetcode.cn/problems/report-spam-message/description/
标签: LeetCode第416场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3295 {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        unordered_set<string> set;
        for (auto &s : bannedWords) {
            set.insert(s);
        }
        int count = 0;
        for (auto &s : message) {
            if (set.count(s)) {
                count++;
                if (count >= 2) return true;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

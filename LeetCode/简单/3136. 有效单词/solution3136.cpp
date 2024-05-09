/*
url: https://leetcode.cn/problems/valid-word/description/
标签: LeetCode第396场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3136 {
public:
    bool isValid(string word) {
        if (word.size() < 3) return false;
        unordered_set<char> mySet = {'a','e','i','o','u','A','E','I','O','U'};
        int count1 = 0; // 元音字母数
        int count2 = 0; // 辅音字母数
        for (char c : word) {
            if (c >= '0' && c <= '9') continue;
            else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                if (mySet.count(c)) count1++;
                else count2++;
            }
            else return false;
        }
        return count1 > 0 && count2 > 0;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

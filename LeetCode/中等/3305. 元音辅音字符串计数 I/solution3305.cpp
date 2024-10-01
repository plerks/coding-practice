/*
url: https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/description/
相关: LeetCode3306. 元音辅音字符串计数 II
标签: LeetCode第417场周赛
*/

// 此题是LeetCode3306. 元音辅音字符串计数 II的数据范围缩小版

#include <bits/stdc++.h>

using namespace std;

class Solution3305 {
public:
    // 直接暴力O(n^2)
    int countOfSubstrings(string word, int k) {
        int n = word.size();
        int ans = 0;
        int mask = 0;
        mask |= 1 << ('a' - 'a');
        mask |= 1 << ('e' - 'a');
        mask |= 1 << ('i' - 'a');
        mask |= 1 << ('o' - 'a');
        mask |= 1 << ('u' - 'a');
        for (int i = 0; i < n; i++) {
            unordered_set<char> set;
            int consonant = 0;
            for (int j = i; j >= 0; j--) {
                if (1 << (word[j] - 'a') & mask) { // 是元音
                    set.insert(word[j]);
                }
                else consonant++;
                if (set.size() == 5 && consonant == k) {
                    ans++;
                }
                if (consonant > k) break;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3305 solu;
    cout << solu.countOfSubstrings("aeioqq", 1) << endl;
    return 0;
}

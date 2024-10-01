/*
url: https://leetcode.cn/problems/find-the-k-th-character-in-string-game-i/description/
相关: LeetCode3307. 找出第 K 个字符 II
标签: LeetCode第417场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3304 {
public:
    char kthCharacter(int k) {
        string s = "a";
        while (s.size() < k) {
            string t = s;
            // 周赛时这里写成了，for (int i = 0; i < t.size(); i++) t[i] += 1; 但是这题数据范围小，没发生需要从z变回a的情况，所以没WA
            for (int i = 0; i < t.size(); i++) t[i] = (t[i] - 'a' + 1) % 26 + 'a';
            s += t;
        }
        return s[k - 1];
    }

    // 见`LeetCode3307. 找出第 K 个字符 II`灵茶山艾府讲解
    char kthCharacter_implementation2(int k) {
        return 'a' + __builtin_popcount(k - 1) % 26;
    } 
};

int main(int argc, char const *argv[]) {
    Solution3304 solu;
    cout << solu.kthCharacter(5) << endl;
    cout << solu.kthCharacter_implementation2(5) << endl;
    return 0;
}

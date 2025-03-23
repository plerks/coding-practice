/*
url: https://leetcode.cn/problems/make-string-a-subsequence-using-cyclic-increments/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2825 {
public:
    bool canMakeSubsequence(string str1, string str2) {
        // 题目选若干个下标变，不一定要连续，也就是说使用变化机会的位置不一定都在中部，直接贪心
        int i = 0, j = 0;
        while (i < str1.size() && j < str2.size()) {
            if (str1[i] == str2[j] || (str1[i] - 'a' + 1) % 26 + 'a' == str2[j]) {
                i++;
                j++;
            }
            else i++;
        }
        return j == str2.size();
    }
};

int main(int argc, char const *argv[]) {
    Solution2825 solu;
    // cout << solu.canMakeSubsequence("abc", "ad") << endl;
    // cout << solu.canMakeSubsequence("zc", "ad") << endl;
    cout << solu.canMakeSubsequence("pc", "qc") << endl;
    return 0;
}
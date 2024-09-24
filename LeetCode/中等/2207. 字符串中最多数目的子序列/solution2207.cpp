/*
url: https://leetcode.cn/problems/maximize-number-of-subsequences-in-a-string/description/?envType=daily-question&envId=2024-09-24
标签: 子序列
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2207 {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        int n = text.size();
        char a = pattern[0];
        char b = pattern[1];
        int counta = 0;
        int countb = 0;
        long long ans = 0;
        // 原有的子序列数
        for (int i = n - 1; i >= 0; i--) {
            if (text[i] == a) {
                counta++;
                ans += countb;
            }
            if (text[i] == b) countb++;
        }
        // 考虑插入一个字符能带来的最大子序列增加数，若插a，一定插在所有b之前，因此只需知道所有a的数目，若插b，一定插在所有a之后，因此只需知道所有b的数目
        
        return ans + max(counta, countb);
    }
};

int main(int argc, char const *argv[]) {
    Solution2207 solu;
    cout << solu.maximumSubsequenceCount("abdcdbc", "ac") << endl;
    return 0;
}

/*
url: https://leetcode.cn/problems/minimum-time-to-revert-word-to-initial-state-i/
参考: https://www.bilibili.com/video/BV1it421W7D8/
相关: 典型问题/Z函数, LeetCode3031. 将单词恢复初始状态所需的最短时间 II
标签: Z函数
*/

#include <bits/stdc++.h>

using namespace std;

// 此题是LeetCode3031. 将单词恢复初始状态所需的最短时间 II的数据范围缩小版

class Solution3029 {
public:
    // 在i位置操作，后缀的部分必须要和前缀匹配
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> z = z_function(word);
        int ans = 0;
        int i = k;
        while (i < n && z[i] != n - i) {
            ans++;
            i += k;
        }
        return ans + 1; // 最后i位置符合了还要操作一次
    }

    vector<int> z_function(string s) {
        int n = s.size();
        vector<int> z(n, 0);
        // z[0] = 0;
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r) {
                z[i] = min(z[i - l], r - i + 1);
            }
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }
};

int main(int argc, char const *argv[]) {
    Solution3029 solu;
    cout << solu.minimumTimeToInitialState("abacaba", 3) << endl;
    return 0;
}

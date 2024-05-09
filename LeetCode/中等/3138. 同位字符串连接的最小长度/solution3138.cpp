/*
url: https://leetcode.cn/problems/minimum-length-of-anagram-concatenation/description/
标签: LeetCode第396场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3138 {
public:
    int minAnagramLength(string s) {
        int n = s.size();
        // 枚举原本的那个字符串的长度
        for (int i = 1; i <= n - 1; i++) {
            if (n % i != 0) continue;
            vector<int> map1(26, 0);
            for (int j = 0; j < i; j++) {
                map1[s[j] - 'a']++;
            }
            // 检查后面每段成分是否与第一段相同
            bool same = true;
            for (int k = 1; k < n / i; k++) {
                // 周赛时这里是这样写的，创建了个string，能通过，可以优化
                /* string sub = s.substr(k * i, i);
                vector<int> map2(26, 0);
                for (int j = 0; j < i; j++) {
                    map2[sub[j] - 'a']++;
                } */
                vector<int> map2(26, 0);
                for (int j = k * i; j < (k + 1) * i; j++) {
                    map2[s[j] - 'a']++;
                }
                for (int i = 0; i < 26; i++) {
                    if (map1[i] != map2[i]) {
                        same = false;
                    }
                }
            }
            if (same) return i;
        }
        return n;
    }
};

int main(int argc, char const *argv[]) {
    Solution3138 solu;
    cout << solu.minAnagramLength("abba") << endl;
    return 0;
}

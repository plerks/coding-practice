/*
url: https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-ii/
标签: 【题单】二分算法, 最大次大第三大, [mark]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2982 {
public:
    int maximumLength(string s) {
        int n = s.size();
        
        auto check = [&](int bound) {
            int cnt[26]{};
            // 分组循环
            for (int i = 0; i < n;) {
                int start = i;
                for (i++; i < n && s[i] == s[i - 1]; i++);
                // [start, i)
                cnt[s[start] - 'a'] += max(0, i - bound - start + 1);
                if (cnt[s[start] - 'a'] >= 3) return true;
            }
            for (int x : cnt) {
                if (x >= 3) return true;
            }
            return false;
        };

        int left = 1, right = n - 2;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right == 0 ? -1 : right;
    }

    /* 参考灵茶题解，不用二分，而是记录每种字符的最大，次大，第三大出现次数。
    若a[0] > a[1]，则可以取出3个长为a[1]的串，也可以3个a[0] - 2的串
    若a[0] == a[1]，则可以取三个a[0] - 1，当a[2]和二者相等时，取三个a[2]的方案更大。
    
    当a[0] > a[1]时，取a[1]，且a[1] <= a[0] - 1;
    当a[0] == a[1]时，取a[0] - 1，且a[0] - 1 <= a[1]，
    所以这两种情况可以合并为min(a[1], a[0] - 1)
    */
    int maximumLength_implementation2(string s) {
        int n = s.size();
        int cnt[26][3]{};
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && s[i] == s[i - 1]; i++);
            // [start, i)
            int freq = i - start;
            int j = s[start] - 'a';
            // 从第一个位置开始，如果比当前位置大，则把右侧部分往右挤，并且完成维护。否则继续尝试下一个位置。这样写最清晰。[mark]
            if (freq > cnt[j][0]) {
                cnt[j][2] = cnt[j][1];
                cnt[j][1] = cnt[j][0];
                cnt[j][0] = freq;
            }
            else if (freq > cnt[j][1]) {
                cnt[j][2] = cnt[j][1];
                cnt[j][1] = freq;
            }
            else if (freq > cnt[j][2]) {
                cnt[j][2] = freq;
            }
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            int *a = cnt[i];
            ans = max({ans, min(a[1], a[0] - 1), a[0] - 2, a[2]});
        }
        return ans == 0 ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2982 solu;
    cout << solu.maximumLength("aaaa") << endl;
    cout << solu.maximumLength("abcaba") << endl;

    cout << solu.maximumLength_implementation2("aa") << endl;
    return 0;
}
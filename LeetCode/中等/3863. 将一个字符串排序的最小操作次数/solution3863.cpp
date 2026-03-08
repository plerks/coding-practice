/*
url: https://leetcode.cn/problems/minimum-operations-to-sort-a-string/
标签: LeetCode第492场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3863 {
public:
    // 周赛时的解法，写得不优，不过能过。能直觉感觉出来操作次数不会太多，然后想先操作 [0, n - 2] 和 [1, n - 1] 就是自然的了
    int minOperations(string s) {
        return min(f1(s), f2(s));
    }

    int f1(string s) {
        int n = s.size();
        if (n == 2 && s[0] > s[1]) return -1;
        bool ok = true;
        for (int i = 1; i < n; i++) if (s[i] < s[i - 1]) ok = false;
        if (ok) return 0;

        char mi = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());
        // 先排 [0, n - 2] ，然后看 s[n - 1] 是第几大
        bool ok2 = true;
        for (int i = 1; i < n - 1; i++) if (s[i] < s[i - 1]) ok2 = false;
        int d = !ok2;
        sort(s.begin(), s.begin() + n - 1);
        if (s[n - 1] == mx) return 0 + d;
        if (s[n - 1] != mi || s[0] == mi) return 1 + d;
        return 2 + d;
    }

    int f2(string s) {
        int n = s.size();
        if (n == 2 && s[0] > s[1]) return -1;
        bool ok = true;
        for (int i = 1; i < n; i++) if (s[i] < s[i - 1]) ok = false;
        if (ok) return 0;

        char mi = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());
        // 先排 [1, n - 1] ，然后看 s[0] 是第几大
        bool ok2 = true;
        for (int i = 2; i < n; i++) if (s[i] < s[i - 1]) ok2 = false;
        int d = !ok2;
        sort(s.begin() + 1, s.end());
        if (s[0] == mi) return 0 + d;
        if (s[0] != mx || s[n - 1] == mx) return 1 + d;
        return 2 + d;
    }

    /* 参考灵茶题解，分类讨论
    如果已有序，ans = 0
    如果无序，且 n = 2，无法操作
    如果无序，且 n > 2，
        如果是 mi ... 或 ... mx ，操作一次即可
        如果中间有最值(注意可能有相等元素)，即 ... {mi, mx} ... 或 mx ... mi ... 或 ... mx ... mi ，先选 n - 1 长度的拍一次就变成上一种情况，共 2 次
        如果是 mx ... mi ，要 3 次
    */
    int minOperations_impl2(string s) {
        if (is_sorted(s.begin(), s.end())) return 0;
        int n = s.size();
        if (n == 2) return -1;
        char mi = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());
        if (s[0] == mi || s[n - 1] == mx) return 1;
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mi || s[i] == mx) return 2;
        }
        return 3;
    }
};

int main(int argc, char const *argv[]) {
    Solution3863 solu;
    cout << solu.minOperations_impl2("card") << endl;
    cout << solu.minOperations_impl2("onon") << endl;
    return 0;
}
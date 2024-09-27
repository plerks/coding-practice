/*
url: https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/description/?envType=daily-question&envId=2024-09-27
参考: https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/solutions/2031995/on-shuang-zhi-zhen-by-endlesscheng-4g9p/
相关: LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I, LeetCode3298. 统计重新排列后包含另一个字符串的子字符串数目 II
标签: 滑动窗口, 滑动窗口例题
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2516 {
public:
    // 这题类似LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I，我还是习惯性地枚举了左边界，但是枚举右边界要清晰点
    int takeCharacters(string s, int k) {
        if (k == 0) return 0;
        int n = s.size();
        int count[3]{};
        for (char c : s) count[c - 'a']++;
        if (!(count[0] >= k && count[1] >= k && count[2] >= k)) return -1;
        int ans = n;
        int j = 0;
        while (j < n && count[s[j] - 'a'] > k) {
            count[s[j] - 'a']--;
            j++;
        }
        ans = min(ans, n - j);
        for (int i = 0; i < n; i++) {
            count[s[i] - 'a']++;
            while (j < n && count[s[j] - 'a'] > k) {
                count[s[j] - 'a']--;
                j++;
            }
            ans = min(ans, i + 1 + n - j);
        }
        return ans;
    }

    // 灵茶山艾府题解做法，枚举右边界，逻辑要清晰些
    int takeCharacters_implementation2(string s, int k) {
        if (k == 0) return 0;
        int n = s.size();
        int count[3]{};
        for (char c : s) count[c - 'a']++;
        if (!(count[0] >= k && count[1] >= k && count[2] >= k)) return -1;
        int ans = n;
        int left = 0;
        for (int right = 0; right < n; right++) {
            count[s[right] - 'a']--;
            while (count[0] < k || count[1] < k || count[2] < k) {
                count[s[left] - 'a']++;
                left++;
            }
            ans = min(ans, left + n - 1 - right);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2516 solu;
    // cout << solu.takeCharacters("aabaaaacaabc", 2) << endl;
    // cout << solu.takeCharacters("acba", 1) << endl;
    cout << solu.takeCharacters("cbbac", 1) << endl;
    cout << solu.takeCharacters_implementation2("cbbac", 1) << endl;
    return 0;
}

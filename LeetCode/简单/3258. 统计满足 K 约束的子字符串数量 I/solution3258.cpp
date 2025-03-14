/*
url: https://leetcode.cn/problems/count-substrings-that-satisfy-k-constraint-i/
相关: LeetCode3261. 统计满足 K 约束的子字符串数量 II
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3258 {
public:
    int countKConstraintSubstrings(string s, int k) {
        int n = s.size();
        int cnt[2]{};
        int ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            cnt[s[r] - '0']++;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[l] - '0']--;
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3258 solu;
    cout << solu.countKConstraintSubstrings("1010101", 2) << endl;
    return 0;
}
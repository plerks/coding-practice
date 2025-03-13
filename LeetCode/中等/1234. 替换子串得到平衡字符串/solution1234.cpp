/*
url: https://leetcode.cn/problems/replace-the-substring-for-balanced-string/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1234 {
public:
    // 我的写法
    int balancedString(string s) {
        int n = s.size();
        int d = n / 4;
        map<char, int> idx;
        idx['Q'] = 0, idx['W'] = 1, idx['E'] = 2, idx['R'] = 3;
        // 枚举选的窗口的右边界，窗口越大越能平衡，有单调性可以滑窗
        int total[4]{}; // QWER总数量
        for (char c : s) total[idx[c]]++;
        
        int inner[4]{}; // 窗口内QWER数量

        auto check = [&](int cnt) { // cnt是操作次数
            int out[4]{};
            // 先把窗口内的都抹除，然后把每个调整到d（只能增加不能减少）
            for (int i = 0; i < 4; i++) out[i] = total[i] - inner[i];
            for (int i = 0; i < 4; i++) {
                if (out[i] > d) return false;
                cnt -= d - out[i];
                if (cnt < 0) return false;
            }
            return true;
        };

        if (check(0)) return 0;

        int ans = n;

        int l = 0;
        for (int r = 0; r < n; r++) {
            inner[idx[s[r]]]++;
            while (l <= r) {
                if (check(r - l + 1)) {
                    inner[idx[s[l]]]--;
                    ans = min(ans, r - l + 1);
                    l++;
                }
                else break;
            }
        }
        return ans;
    }

    // 灵茶题解写法，只要外部出现次数都<=n/4就一定能操作使之均衡，不需要去模拟，判断逻辑上也简洁很多
    int balancedString_implementation2(string s) {
        int n = s.size();
        int m = n / 4;
        int cnt['X']{};
        for (char c : s) {
            cnt[c]++;
        }
        if (cnt['Q'] == m && cnt['W'] == m && cnt['E'] == m && cnt['R'] == m) return 0;
        int ans = n, l = 0;
        for (int r = 0; r < n; r++) {
            cnt[s[r]]--; // 进入窗口时--，就能自然维护外部的字符数量
            while (cnt['Q'] <= m && cnt['W'] <= m && cnt['E'] <= m && cnt['R'] <= m) {
                ans = min(ans, r - l + 1);
                cnt[s[l]]++;
                l++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1234 solu;
    // cout << solu.balancedString("QWER") << endl;
    cout << solu.balancedString("QQWE") << endl;
    cout << solu.balancedString_implementation2("QQWE") << endl;
    return 0;
}
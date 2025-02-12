/*
url: https://leetcode.cn/problems/length-of-the-longest-valid-substring/
参考: https://leetcode.cn/problems/length-of-the-longest-valid-substring/solutions/2345796/ha-xi-biao-shuang-zhi-zhen-pythonjavacgo-bcez/
标签: 【题单】滑动窗口与双指针, 右端点筛选, 考虑值域
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2781 {
public:
    /* 参考灵茶题解，
    1 <= forbidden[i].length <= 10，所以为了检查[l, r]中是否有forbidden，只需枚举长度1-10就行了，这个开销并不大。
    注意每次r移动时，从右端点筛选，所以只需检查当前的r即可。
    */
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int n = word.size();
        string_view s(word);
        unordered_set<string_view> st(forbidden.begin(), forbidden.end());
        int l = 0;

        auto check = [&](int l, int r) {
            for (int k = 1; r - k + 1 >= l && k <= 10; k++) {
                if (st.count(s.substr(r - k + 1, k))) return true;
            }
            return false;
        };

        int ans = 0;
        for (int r = 0; r < n; r++) {
            while (l <= r && check(l, r)) {
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2781 solu;
    cout << solu.longestValidSubstring("cbaaaabc", *new vector<string>{"aaa","cb"}) << endl;
    return 0;
}
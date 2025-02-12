/*
url: https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/
参考: https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/solutions/623432/zhi-shao-you-kge-zhong-fu-zi-fu-de-zui-c-o6ww/
      https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/solutions/624045/xiang-jie-mei-ju-shuang-zhi-zhen-jie-fa-50ri1/
      https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/solutions/623432/zhi-shao-you-kge-zhong-fu-zi-fu-de-zui-c-o6ww/comments/2275757
相关: LeetCode1763. 最长的美好子字符串
标签: 【题单】滑动窗口与双指针, 考虑值域
*/

#include <bits/stdc++.h>

using namespace std;

class Solution395 {
public:
    /* 参考官方题解，滑动窗口
    这题不能直接用滑动窗口，对于某个r，l往左往右都可能是正解，往左是为了增加频率(比如r新引入了字母'b')，但是往右能直接把所有某个字母挤出，到0就不用考虑k频率的
    限制了，所以这题没有直接的单调性。
    更改约束，限制窗口中出现的字符种数<=t，窗口在滑动过程中保持极大，若r是已有字符，则l不动，若r是新字符，则l不动(窗口字符种数还<k)或向右。
    这样一来，窗口的约束就会完全变为字符种数，这样l的运动是单调的，要做的只是在滑动过程中检查频率是否够k。
    这个滑窗思路很巧妙，换了一个约束，把不能滑窗的变成了可以滑窗的。
    */
    int longestSubstring(string s, int k) {
        int n = s.size();
        int ans = 0;
        for (int t = 1; t <= 26; t++) {
            int all = 0; // 窗口内的字母种类数
            int cnt = 0; // 窗口内频率>=k的字母数
            int freq[26]{};
            int l = 0;
            for (int r = 0; r < n; r++) {
                freq[s[r] - 'a']++;
                if (freq[s[r] - 'a'] == 1) all++;
                if (freq[s[r] - 'a'] == k) cnt++;
                /* 注意这里滑窗写法的 l <= r 限制，是否需要写l<=r和具体题目有关，
                窗口长度如果可能移动到长度为0（此时l == r + 1），那么当 r == n - 1 时，l就会越界，
                但是，可能题目性质自动限制了最少到窗口长度为1时就会停止（此时l == r），那么就不用写l <= r的限制。
                此题当窗口只有一个元素时all>t一定为false，**空区间不会进去循环**，所以实际可以不用写l <= r的限制。
                */
                while (l <= r && all > t) {
                    freq[s[l] - 'a']--;
                    if (freq[s[l] - 'a'] == 0) all--;
                    if (freq[s[l] - 'a'] == k - 1) cnt--;
                    l++;
                }
                if (all == cnt) ans = max(ans, r - l + 1);
            }
        }
        return ans;
    }

    /* 官方题解的另一种解法，分治，代码写法参考[评论区](https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/solutions/623432/zhi-shao-you-kge-zhong-fu-zi-fu-de-zui-c-o6ww/comments/2275757)
    子串应该尽量长，但若s中某个字母的出现次数 > 0 && < k，则这个字母一定不能选用，通过这个字母可以将s分割，
    然后对分割后的子串递归，虽然看起来比较暴力，但是由于每次都会完全删除某个字母，所以递归深度最多26，而每层递归实例
    的开销和为O(n)，因此时间复杂度为O(26n)
    */
    int longestSubstring_implementation2(string s, int k) {
        int ans = 0;

        // 可以不用定义一个新的dfs()函数直接用longestSubstring()递归
        auto dfs = [&](auto &dfs, string_view s) -> void {
            int n = s.size();
            int cnt[26]{};
            for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
            // 这个手动split合法段有分组循环的感觉
            for (int i = 0; i < n; i++) {
                // 手动split合法段
                while (i < n && cnt[s[i] - 'a'] < k) i++;
                int start = i;
                while (i < n && cnt[s[i] - 'a'] >= k) i++;
                // 递归基，全是合法字母，没有规模更小的子问题。属于少见的不是写在递归函数开头的递归基
                if (i - start == n) {
                    ans = max(ans, n);
                    return;
                }
                dfs(dfs, s.substr(start, i - start));
            }
        };
        
        dfs(dfs, s);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution395 solu;
    cout << solu.longestSubstring("aaabb", 3) << endl;
    // cout << solu.longestSubstring("ababacb", 3) << endl;
    
    cout << solu.longestSubstring_implementation2("aaabb", 3) << endl;
    return 0;
}
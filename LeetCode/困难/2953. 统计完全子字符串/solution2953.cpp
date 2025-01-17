/*
url: https://leetcode.cn/problems/count-complete-substrings/description/
参考: https://leetcode.cn/problems/count-complete-substrings/solutions/2551743/bao-li-hua-chuang-mei-ju-chuang-kou-nei-31j5m/
      https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/solutions/2528771/jiao-ni-yi-ci-xing-ba-dai-ma-xie-dui-on-zuspx/
相关: LeetCode2760. 最长奇偶子数组
标签: 【题单】滑动窗口与双指针, 考虑值域, 右端点筛选, 分组循环, 动态维护
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2953 {
public:
    /* 不知道怎么处理有多种字母的情况，iigg能有2个串，igig只有一个。
    参考灵茶山艾府题解，枚举窗口大小，因为都是小写字母，窗口最多26种大小(i * k)，算是在考虑值域。
    这题有相邻字母之差不能超过2的限制，直接先初始化滑窗中间可能有非法的位置(这提醒我们r不能直接就从len - 1开始)，
    我直接写写成了以下这样，虽然没问题但是这种没一个固定的for循环，两个指针都在动的写法很容易错，还是要用枚举一端，移动另一端的写法才好。

    时间复杂度O(26n)
    */
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int ans = 0;

        auto calc = [&](int d) {
            int map[26]{}; // 字符出现次数
            int count = 0; // 记录有多少个字母的出现次数等于k，动态维护而非每次把map全读一遍
            int len = d * k;
            // 虽然每次窗口应该是定长的，但是还有个条件是相邻字母之差不能超过2，得按不定长的窗口来写
            int l = 0, r = 0;
            // 这里的双指针有点分组循环的味道 (https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/solutions/2528771/jiao-ni-yi-ci-xing-ba-dai-ma-xie-dui-on-zuspx/)
            while (r < n) { // 也可以 while (l <= n - len)
                while (r < n && r - l + 1 <= len) {
                    if (r > 0 && r - 1 >= l && abs(word[r] - word[r - 1]) > 2) {
                        l = r;
                        for (int& x : map) x = 0;
                        count = 0;
                        break;
                    }
                    else {
                        // r可以加入
                        map[word[r] - 'a']++;
                        if (map[word[r] - 'a'] == k) count++;
                        else if (map[word[r] - 'a'] == k + 1) count--;
                        if (r - l + 1 == len) {
                            if (count == d) ans++;
                            map[word[r - len + 1] - 'a']--;
                            if (map[word[r - len + 1] - 'a'] == k) count++;
                            else if (map[word[r - len + 1] - 'a'] == k - 1) count--;
                            l++;
                        }
                        r++;
                    }
                }
            }
        };

        // 枚举窗口中的字母种类个数，考虑窗口长度
        for (int d = 1; d <= 26; d++) {
            if (d * k > n) break;
            calc(d);
        }
        return ans;
    }

    // 改下双指针的写法，参考<https://leetcode.cn/problems/count-complete-substrings/solutions/2551743/bao-li-hua-chuang-mei-ju-chuang-kou-nei-31j5m/comments/2276677>
    int countCompleteSubstrings_implementation2(string word, int k) {
        int n = word.size();
        int ans = 0;

        auto calc = [&](int d) {
            int map[26]{};
            int count = 0; // 记录有多少个字母的出现次数等于k
            int len = d * k;
            int l = 0;
            for (int r = 0; r < n; r++) { // 维持窗口的字母都满足相邻之差<=2，还是要用右端点来进行剔除
                map[word[r] - 'a']++;
                if (map[word[r] - 'a'] == k) count++;
                else if (map[word[r] - 'a'] == k + 1) count--;
                while (l < r && (map[word[r] - 'a'] > k || (r > 0 && (abs(word[r] - word[r - 1]) > 2)))) {
                    map[word[l] - 'a']--;
                    if (map[word[l] - 'a'] == k) count++;
                    else if (map[word[l] - 'a'] == k - 1) count--;
                    l++;
                }
                // 窗口长度不会大于len，每次刚到len都会缩减一下
                if (r - l + 1 == len) {
                    if (count == d) ans++;
                    map[word[l] - 'a']--;
                    if (map[word[l] - 'a'] == k) count++;
                    else if (map[word[l] - 'a'] == k - 1) count--;
                    l++;
                }
            }
            return ans;
        };

        // 枚举窗口中的字母种类个数，考虑窗口长度
        for (int d = 1; d <= 26; d++) {
            if (d * k > n) break;
            calc(d);
        }
        return ans;
    }

    // 灵茶山艾府解法，相邻差<=2的部分构成多个段，先用分组循环的技巧把这些段分别找出来再滑窗，时间复杂度O(26n)
    int countCompleteSubstrings_implementation3(string word, int k) {
        int n = word.size();
        int ans = 0;
        string_view sv(word);

        auto calc = [&](const string_view& s) { // 进来的string_view已经满足了相邻之差<=2的条件
            for (int d = 1; d <= 26; d++) {
                int map[26]{};
                int count = 0;
                int len = d * k;
                int l = 0;
                for (int r = 0; r < s.size(); r++) {
                    map[s[r] - 'a']++;
                    if (map[s[r] - 'a'] == k) count++;
                    else if (map[s[r] - 'a'] == k + 1) count--;
                    while (l <= r && map[s[r] - 'a'] > k) {
                        map[s[l] - 'a']--;
                        if (map[s[l] - 'a'] == k) count++;
                        else if (map[s[l] - 'a'] == k - 1) count--;
                        l++;
                    }
                    if (r - l + 1 == len) {
                        if (count == d) ans++;
                        map[s[l] - 'a']--;
                        if (map[s[l] - 'a'] == k) count++;
                        else if (map[s[l] - 'a'] == k - 1) count--;
                        l++;
                    }
                }
            }
        };

        // 分组循环，把每个相邻差<=2的极大段都找出来，这些段只在端点处有相交
        for (int i = 0; i < n;) { // i不会在这里++，相当于while(i < n)
            int start = i; // 记好开始位置
            for (i++; i < n && abs(word[i] - word[i - 1]) <= 2; i++); // 用i去找结束位置
            
            // [start, i - 1]为找出的合法段
            calc(sv.substr(start, i - start));
        }
        return ans;
    }

    /* 注意这样写是会超时的，这题如果枚举并固定左端点，然后枚举窗口长度，时间复杂度会是O(n * 26 * k)，
    很多窗口的重合部分被重复计算了，这题1 <= k <= word.length，会超时
    */
    int countCompleteSubstrings_tle(string word, int k) {
        int n = word.size();
        int ans = 0;

        // 这里写不写 string_view& 差距不大
        auto calc = [&](string_view s) {
            // 枚举窗口长度
            int map[26]{}; // 字母出现次数
            int count = 0; // 记录有多少个字母的出现次数等于k
            int p = 0;
            bool over = false; // 左端点固定在了s[0]，如果有一个字母已经超过k或者相邻差>2，后面不用看了
            for (int d = 1; d <= 26; d++) {
                while (p < s.size() && p <= d * k - 1) {
                    map[s[p] - 'a']++;
                    if (map[s[p] - 'a'] == k) count++;
                    else if (map[s[p] - 'a'] == k + 1) count--;
                    if (map[s[p] - 'a'] > k || (p > 0 && abs(s[p] - s[p - 1]) > 2)) over = true;
                    p++;
                }
                if (over) break;
                if (p == d * k && count == d) {
                    ans++;
                }
            }
        };

        string_view sv(word); // string_view的substr是零拷贝的
        for (int i = 0; i < n; i++) {
            calc(sv.substr(i));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2953 solu;
    // cout << solu.countCompleteSubstrings("igigee", 2) << endl;
    // cout << solu.countCompleteSubstrings("gvgvvgv", 2) << endl;
    // cout << solu.countCompleteSubstrings("a", 1) << endl;

    cout << solu.countCompleteSubstrings_implementation2("gvgvvgv", 2) << endl;

    cout << solu.countCompleteSubstrings_implementation3("igigee", 2) << endl;
    return 0;
}
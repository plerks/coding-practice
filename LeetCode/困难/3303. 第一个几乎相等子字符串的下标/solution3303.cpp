/*
url: https://leetcode.cn/problems/find-the-occurrence-of-first-almost-equal-substring/description/
参考: https://leetcode.cn/problems/find-the-occurrence-of-first-almost-equal-substring/solutions/2934098/qian-hou-zhui-fen-jie-z-shu-zu-pythonjav-0est/
      https://leetcode.cn/problems/find-the-occurrence-of-first-almost-equal-substring/solutions/2933927/er-fen-ha-xi-by-tsreaper-5ox7/
相关: LeetCode3302. 字典序最小的合法序列, 典型问题/Z函数
标签: LeetCode第140场双周赛, 前后缀分解, 前后缀分解例题, 字符串, 子字符串, 子串
*/

// 这次双周赛2题

#include <bits/stdc++.h>

using namespace std;

// 这题暴力要O(n^2)，虽然容易发现中间有很多重复的读字符与比较，但是想不到要怎么神奇地优化到O(n)
class Solution3303 {
public:
    int minStartingIndex(string s, string pattern) {
        /* 先不考虑可以修改一次，当p在s的i位置匹配时，从i到i + pattern.size() - 1，字符全部匹配。
        但是，可以修改一次字符，于是可能i只能匹配到j位置，然后j + 1位置s和pattern字符不同，为了处理这个问题，
        从i位置往右看，找s从i开始能匹配pattern的最大子串长度，从i + pattern.size() - 1位置往左看，找能匹配的最大长度，
        如果长度之和+1 >= pattern.size()，说明可以修改成pattern。而找s从i开始能匹配pattern的最大子串长度是Z函数的场景。
        */
        // 把s和p拼起来直接套Z函数的模板
        int n = s.size(), m = pattern.size();
        string ps1 = pattern + s;
        auto z1 = z_function(ps1);

        reverse(pattern.begin(), pattern.end());
        reverse(s.begin(), s.end()); // 反两次套Z函数，这里有点绕，注意想要的是s和p从右往左匹配，所以先反转下，变成求s和p从左往右匹配再套Z函数
        string ps2 = pattern + s;
        auto z2 = z_function(ps2);

        for (int i = 0; i + m <= n; i++) {
            if (z1[i + m] + z2[n - i] + 1 >= m) return i;
        }
        return -1;
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

/*
灵茶山艾府题解还提了2个变式和解答

变式1：如果题目变为至多k个连续字符可以被修改，如何求解？
z1[i + m] + z2[n - i] + 1 >= m 变为 z1[i + m] + z2[n - i] + k >= m 即可

变式2：使答案存在的最小的 k 是多少？
这时我们不需关心最小可匹配的下标，枚举i的过程中，前缀和后缀匹配中间有个空缺的长度，记其最小值即可，
即max(m - z1[i + m] - z2[n - i], 0)的最小值
*/

/* 还有种用字符串哈希的办法，见<https://leetcode.cn/problems/find-the-occurrence-of-first-almost-equal-substring/solutions/2933927/er-fen-ha-xi-by-tsreaper-5ox7/>，
时间复杂度O(nlogn)，不比minStartingIndex()的O(n)时间好，且字符串哈希有极低的概率碰撞的问题。
但是这种方法很奇特，对每个匹配开始位置i，二分长度，找第一个不相等的字符（check的条件是字符串哈希值是否相等，字符串哈希在O(1)时间给出
某段字符串的哈希值，而长度越长，s和p对应子串的哈希值从相等到不等变化），找到第一个不相等的字符位置后，用掉修改的机会，然后再用字符串哈希
在O(1)时间判断后面部分是否相等。
*/

int main(int argc, char const *argv[]) {
    Solution3303 solu;
    cout << solu.minStartingIndex("abcdefg", "bcdffg") << endl;
    return 0;
}

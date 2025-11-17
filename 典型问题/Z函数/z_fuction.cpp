/*
描述: 对于一个字符串s，z[i]表示s和s[i, n - 1]的匹配长度（即s的前缀和以s[i]开头的后缀的匹配长度），算法以O(n)时间计算出z函数数组
参考: https://oi-wiki.org/string/z-func/
      https://www.bilibili.com/video/BV1it421W7D8/
相关: LeetCode3031. 将单词恢复初始状态所需的最短时间 II, LeetCode3303. 第一个几乎相等子字符串的下标, 洛谷P5410
*/

// 把pattern拼接到s前面然后求Z数组，然后遍历s的位置看匹配长度是否>=pattern.size()，可以达到kmp相同的效果

#include <bits/stdc++.h>

using namespace std;

/*
将i位置匹配到的窗口[i, i + z[i] - 1]叫做Z-box。考虑计算z[i]，当i位置落在某个之前的Z-box [l, r]中时，由Z-box的定义，
可以直接知道[i, r]是和[i - l, r - l]相等的，那么[i - l, r - l]和s的匹配，也会是[i, r]和s的匹配，于是可由之前的经验
z[i - l]直接得到从i开始的一段匹配，然后再往右暴力枚举。（用之前的经验来减少计算，有点像kmp）

以示例图.jpg为例，[l, r]与[0, r - l]匹配，则[i, r]和[i - l, r - l]相等，通过z[i - l]找i开头的一段匹配。

每个开头位置都有个Z-box，我们期望的是，计算i位置时，让i落在Z-box内，这样我们可以用之前的经验减少计算，因此，我们要记录的
[l, r]，是右端点最靠右的Z-box（左端点不用管，当前计算的位置i一定大于之前的所有Z-box的左端点），这样才能让i尽量落在某个Z-box内。

若z[i - l] < r - i + 1，则z[i] = z[i - l]
若z[i - l] >= r - i + 1，则至少z[i] = r - i + 1，这时还需要枚举去看r右边是否还能扩展
    事实上如果 z[i - l] > r - i + 1，z[i]一定刚好是 r - i + 1 (恰匹配满Z-box)
        因为 s[hi - lo + 1] != s[hi + 1]，而由于 z[i - l] > r - i + 1，故 s[hi - lo + 1] == s[r - i + 1]，即 s[hi + 1] != s[r - i + 1]，下次匹配一定失败
    只有 z[i - l] == r - i + 1 的情况才需要用while去尝试延长
    也就是说可以写成 Luogu/p5410.cpp 里那样
    不过为了代码简洁可以不考虑这一点，因为接下来的匹配一定失败，while会多进一下循环然后马上退出，不影响时间复杂度

如果i在Z-box之外(落在右边)，也是直接暴力枚举

z[i]确定后，如果i + z[i] - 1 > r，更新[l, r]，令l = i, r = i + z[i] - 1

时间复杂度: 外层循环O(n)；内层while循环，若z[i - l] < r - i + 1，下一次字符肯定不匹配，不会进while循环，
若z[i - l] >= r - i + 1，则要么不进循环，要么使得r严格单增，所以，整体的while循环时间复杂度也是O(n)。总体时间复杂度O(n)。
*/

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = s.size();
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

int main(int argc, char const *argv[]) {
    auto a = z_function("aaabaab");
    for (int x : a) cout << x << " " << endl;
    return 0;
}
/*
url: https://www.acwing.com/problem/content/294/
参考: https://www.acwing.com/video/557/
相关: LeetCode1349. 参加考试的最大学生数, AcWing291. 蒙德里安的梦想, LeetCode2617. 网格图中最少访问的格子数
标签: 状压dp, 滚动数组, 滚动数组优化, dp设法, dp定义优化
*/

#include <bits/stdc++.h>

using namespace std;

/*
这题和`LeetCode1349. 参加考试的最大学生数`很像。
这样写过不了
输入：
10 5
PHHPP
HPPHP
PPHPP
PPPPP
PPPPP
PPHPP
PPHPP
HPPPH
HPHHH
HPHPH
输出：
15
这个用例，会给出错误输出16。
问题在于，这题某一行能影响到上面2行，而不止是上面1行。
枚举第i行的状态s，再枚举第i - 1行的状态t，再计算第i - 2行的初始状态rowN2，dp[i - 2][rowN2]所对应的最优解可能会被
第i - 1行影响(也就是说dp[i - 2][rowN2]所对应的最优解在第i - 3行可能会与第i - 1行冲突)。
所以这题和`LeetCode1349. 参加考试的最大学生数`还有区别，不能这样写。
*/
int main_wrong(int argc, char const *argv[]) {
    int m, n;
    cin >> m >> n; // m行n列，输入数据范围列数<=10
    /* 对一个位置，需要考虑选与不选，选与不选又会影响其它位置，所以这题具有规划的特征。
    但是选一个位置会影响上下左右4个方位，不是单纯只需要考虑左上角区域的类型，所以是
    状压dp，类似LeetCode1349. 参加考试的最大学生数。
    */
    vector<int> states(m); // 每行的状态，1可以安排炮，0不可以
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'P') {
                states[i] |= 1 << (n - 1 - j);
            }
        }
    }
    vector<vector<int>> dp(m, vector<int>(1 << n)); // dp[i][j]表示第i行初始状态为j时的最大安排炮数
    // 第一行
    for (int j = states[0]; j > 0; j = (j - 1) & states[0]) {
        int x = j;
        // 贪心计算第一行对应状态最大可安排炮数
        int count = 0;
        while (x != 0) {
            int lowbit = x & -x;
            count++;
            // lowbit左边两个位置都得变成0
            x &= ~(lowbit + (lowbit << 1) + (lowbit << 2));
        }
        dp[0][j] = count;
    }
    // 第二行
    for (int j = states[1]; j > 0; j = (j - 1) & states[1]) {
        dp[1][j] = dp[0][states[0]]; // 第2行的1全不安排炮，不影响上面行的情况
        for (int s = j; s > 0; s = (s - 1) & j) { // 枚举第2行初始状态为j的所有坐法
            if ((s & (s >> 1)) == 0 && (s & (s >> 2)) == 0) { // 无距离为1或为2的相邻1
                int rowN1 = states[0] & ~s; // 第1行的初始状态
                dp[1][j] = max(dp[1][j], dp[0][rowN1] + __builtin_popcount(s));
            }
        }
        dp[1][0] = dp[0][states[0]];
    }
    for (int i = 2; i < m; i++) {
        for (int j = states[i]; j > 0; j = (j - 1) & states[i]) {
            dp[i][j] = dp[i - 1][states[i - 1]]; // 第i行的1全不安排炮，不影响上面行的情况
            for (int s = j; s > 0; s = (s - 1) & j) { // 枚举第i行初始状态为j的所有坐法
                if ((s & (s >> 1)) == 0 && (s & (s >> 2)) == 0) { // 无距离为1或为2的相邻1
                    int rowN1 = states[i - 1] & ~s; // i - 1行的初始状态
                    for (int t = rowN1; t > 0; t = (t - 1) & rowN1) { // 枚举i - 1行的所有坐法
                        if ((t & (t >> 1)) == 0 && (t & (t >> 2)) == 0) {
                            int rowN2 = states[i - 2] & ~s & ~t; // 第i - 2行的初始状态，第i和第i - 1行为1的位置，第i - 2行都不能为1
                            dp[i][j] = max(dp[i][j], dp[i - 2][rowN2] + __builtin_popcount(s) + __builtin_popcount(t));
                        }
                    }
                }
            }
        }
        dp[i][0] = dp[i - 1][states[i - 1]];
    }
    cout << dp[m - 1][states[m - 1]] << endl;
    return 0;
}

/* main_wrong()的问题在于，在枚举上面行的状态并检查合法性时，由于一行会影响前2行，所以检查合法性会一直递归下去。
换一个设法，设dp[i][j][k]为**前i行已摆放好，且第i行状态为j，第i - 1行状态为k，且前i行摆放是合法的的最大炮兵数量。**
注意这里的设法j, k为确定的状态，而非上面设法的初始状态，由于牵涉到多行，这样设才能处理，否则根本不知道例如i - 1初始状态
为s的情况下实际选择出的方案是什么样的，也就无法与i - 2行判断合法性。
这样，求递推到i + 1行时，只需考虑第i+1行与前两行的合法性即可。
这里改变了dp设法，要让dp数组的定义有更优秀的性质，这里这种改变设法获得完全不同的效果在`LeetCode2617. 网格图中最少访问的格子数`也有发生。
*/
// 超内存了，用滚动数组优化
int main_memory_limit_exceeded(int argc, char const *argv[]) {
    int m, n;
    cin >> m >> n; // m行n列，输入数据范围列数<=10
    vector<int> g(m); // 每行的状态，1可以安排炮，0不可以
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'P') {
                g[i] |= 1 << (n - 1 - j);
            }
        }
    }
    // 预处理记录同一行炮兵距离>=2的状态
    vector<int> states;
    for (int i = 0; i < (1 << n); i++) {
        if ((i & (i >> 1)) == 0 && (i & (i >> 2)) == 0) {
            states.push_back(i);
        }
    }
    // dp[i][j][k]表示前i行已合法摆放，且第i行状态为j，第i - 1行为k的最大可摆放炮数
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(1 << n, vector<int>(1 << n, 0)));
    // 第一行
    for (int state : states) {
        if ((state & g[0]) == state) { // (state & g[0]) == state代表state是g[0]的子集，也就是说state没有在不能安排炮的地方安排炮
            dp[0][state][0] = __builtin_popcount(state);
        }
    }
    // 第二行
    for (int j : states) {
        for (int k : states) {
            if ((j & g[1]) == j && (j & k) == 0) {
                dp[1][j][k] = dp[0][k][0] + __builtin_popcount(j);
            }
        }
    }
    for (int i = 2; i < m; i++) {
        for (int j : states) { // 第i行
            for (int k : states) { // 第i - 1行
                for (int u : states) { // 第i - 2行
                    if ((j & g[i]) == j && ((j & k) == 0) && ((j & u) == 0)) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][u] + __builtin_popcount(j));
                    }
                }
            }
        }
    }
    int ans = INT_MIN;
    for (int j : states) { // 第i行
        for (int k : states) { // 第i - 1行
            ans = max(ans, dp[m - 1][j][k]);
        }
    }
    cout << ans << endl;
    return 0;
}

// 用滚动数组优化空间使用
int main(int argc, char const *argv[]) {
    int m, n;
    cin >> m >> n; // m行n列，输入数据范围列数<=10
    vector<int> g(m); // 每行的状态，1可以安排炮，0不可以
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'P') {
                g[i] |= 1 << (n - 1 - j);
            }
        }
    }
    // 预处理记录同一行炮兵距离>=2的状态
    vector<int> states;
    for (int i = 0; i < (1 << n); i++) {
        if ((i & (i >> 1)) == 0 && (i & (i >> 2)) == 0) {
            states.push_back(i);
        }
    }
    // dp[i][j][k]表示前i行已合法摆放，且第i行状态为j，第i - 1行为k的最大可摆放炮数
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(1 << n, vector<int>(1 << n, 0)));
    /* 用滚动数组替换dpFull(m, vector<vector<int>>(1 << n, vector<int>(1 << n, 0)))，dp时只涉及到本行与上一行，
    因此滚动数组只需要2行即可。这里dpFull[0]没有前面的行dpFull[-1]，刚好可以用滑动数组全0取代(相当于[-2, -1]也铺了个数组)，不用特判计算边界条件。
    滑动数组行数为w，相当于用行数为w的窗口平移铺满行数为m - 1的dpFull，dpFull[i]对应的dp[]行号为dp[i % w]。
    注意当还没计算完第一个窗口时，计算dpFull[i]时，依赖的上面的行依次是dp[(i - 1) % w], dp[(i - 2) % w], ... dp[(i - k) % w] (1 <= k < w)，
    注意i - k可能为负数，最好写成(i - k + w) % w，也可以单独处理dpFull的前w行，相当于先特判把初始的窗口全算出来，这样就不涉及i - k可能为负数。

    这里由于窗口w大小为2为2的幂次，x % 2^n等价于x & (2^n - 1)，所以可以直接用位运算求i前面的行，这里即使i - k可能为负用& (2^n - 1)也不会有问题，原因在于：
    i - k > -2^n，则-(i - k) < 2^n，则-(i - k)第n位往上一定为0，则lowbit在[0, n - 1]位，(i - k)相对-(i - k)，从lowbit往高位全为1，则
    则(i - k + 2^n)的效果是把第n位往上全变为0，则(i - k + 2^n) % 2^n与(i - k) & (2^n - 1)相等。
    */
    for (int i = 0; i < m; i++) {
        for (int j : states) { // 第i行
            if ((j & g[i]) != j) continue; // 直接剪枝，对i - 1行和i - 2行也可以这样剪，不过要判断下i >= 2
            for (int k : states) { // 第i - 1行
                for (int u : states) { // 第i - 2行
                    // 注意不要写成j & k == 0，==会优先于&先算，C++位运算优先级的坑，Java里运算优先级一样，但是会因为int & boolean报错
                    if (((j & k) == 0) && ((j & u) == 0)) {
                        // 这里也可以写成dp[i % 2][j][k] = max(dp[i % 2][j][k], dp[(i - 1 + 2) % 2][k][u] + __builtin_popcount(j));
                        dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[(i - 1) & 1][k][u] + __builtin_popcount(j));
                    }
                }
            }
        }
    }
    int ans = INT_MIN;
    for (int j : states) { // 第i行
        for (int k : states) { // 第i - 1行
            // 这里也可以写成ans = max(ans, dp[(m - 1 + 2) % 2][j][k]);
            ans = max(ans, dp[(m - 1) & 1][j][k]);
        }
    }
    cout << ans << endl;
    return 0;
}

/*
一个用例
输入：
5 4
PHPP
PPHH
PPPP
PHPP
PHHP
输出：
6
*/
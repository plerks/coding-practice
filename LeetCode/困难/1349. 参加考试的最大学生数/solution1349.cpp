/*
url: https://leetcode.cn/problems/maximum-students-taking-exam/description/
LeetCode参考: https://leetcode.cn/problems/maximum-students-taking-exam/solutions/2580043/jiao-ni-yi-bu-bu-si-kao-dong-tai-gui-hua-9y5k/
相关: AcWing291. 蒙德里安的梦想, AcWing292. 炮兵阵地
标签: 状态压缩dp, 状压dp, 位运算
*/

#include <bits/stdc++.h>

using namespace std;

/* 这题思维量大，用到的位运算技巧多，递归到记忆化搜索到dp也比较典型，有典型例题的价值 */

// 这题一个位置会影响左，左上，右，右上的位置，不是一般的一个位置取决于左上角的子问题的情况，所以不能普通dp，这里实际是状态压缩之后按行dp的

class Solution1349 {
public:
    /* 灵茶山艾府题解解法一，递归，初步思考的解法，所以50 / 57 个通过的测试用例，超时。
    由于一个位置会影响左，左上，右，右上的位置，因此不是普通的dp，需要按行来进行dp。
    状态压缩，这题seats行列数都是<=8的，因此可以用一个int状压来表示某一行的状态。用1表示当前行座位可用，0表示当前行座位不可用。
    用dfs(i, j)表示第i行状态为j(j的每个位表示了第i行的座位状态)时，前i-1行可坐的最大学生数量。
    */
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> states(m); // state[i]表示一开始第i行的座位状态，位为1表示那个位置座位可用
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') {
                    states[i] |= 1 << (n - 1 - j);
                }
            }
        }
        return dfs(m - 1, states[m - 1], states);
    }

    int dfs(int i, int state, vector<int> &states) {
        // 递归基
        if (i == 0) {
            // 当前到了第0行，且第0行状态为state，上面没有行了，需要直接求第0行能坐下的学生数，如何求第0行为state时能坐下的学生数？
            if (state == 0) return 0; // state == 0说明每个位置都不可用
            /* 第0行为state时最多坐的学生数，贪心，从最低位的1开始让学生坐上去，并让这个最低位1和相邻的左侧位置都不可用，然后递归 */
            int lowbit = state & -state;
            // 把最低位1和左侧相邻位置都变0，相当于state &= ~(lowbit + (lowbit << 1)) = ~(lowbit * 3)
            return dfs(i, state & ~(lowbit * 3), states) + 1;
        }
        int ans = dfs(i - 1, states[i - 1], states); // 第i行一个人都不坐，不限制上一行，后面开始枚举时j中的1全表示坐上人了
        // 枚举第i行的坐法，第i行的合法坐法是没有相邻的1，这可以通过(j & (j >> 1)) == 0检测
        // 由于可用位置记为1，现在state是表示本行没坐人，只考虑了有坏座位的情况下，所以state是最大的情况
        for (int j = state; j > 0; j = (j - 1) & state) { // 每次j--后要& state才是下一个要尝试的状态
            if ((j & (j >> 1)) == 0) {
                // 现在j是第i行的状态，让为1的位代表有人坐上去，如何知道第i-1行的那个最大的开始枚举的state?
                // 用states[i - 1] & ~(j << 1 | j >> 1)，因为第i行的1会要求第i-1行左右位置不能为1
                int previousRowInitState = states[i - 1] & ~(j << 1 | j >> 1);
                ans = max(ans, dfs(i - 1, previousRowInitState, states) + __builtin_popcount(j)); // __builtin_popcount()统计二进制位中1的个数，对应的Java方法是Integer.bitCount()
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法二，加上记忆化搜索
    int maxStudents_implementation2(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> states(m); // state[i]表示一开始第i行的座位状态，位为1表示那个位置座位可用
        vector<vector<int>> memo(m, vector<int>(1 << n, -1)); // 记忆化搜索
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') {
                    states[i] |= 1 << (n - 1 - j);
                }
            }
        }
        return dfs(m - 1, states[m - 1], states, memo);
    }

    int dfs(int i, int state, vector<int> &states, vector<vector<int>>& memo) {
        if (memo[i][state] != -1) return memo[i][state];
        // 递归基
        if (i == 0) {
            // 当前到了第0行，且第0行状态为state，上面没有行了，需要直接求第0行能坐下的学生数，如何求第0行为state时能坐下的学生数？
            if (state == 0) return 0; // state == 0说明每个位置都不可用
            /* 第0行为state时最多坐的学生数，贪心，从最低位的1开始让学生坐上去，并让这个最低位1和相邻的左侧位置都不可用，然后递归 */
            int lowbit = state & -state;
            // 把最低位1和左侧相邻位置都变0，相当于state &= ~(lowbit + (lowbit << 1)) = ~(lowbit * 3)
            return dfs(i, state & ~(lowbit * 3), states, memo) + 1;
        }
        int ans = dfs(i - 1, states[i - 1], states, memo); // 第i行一个人都不坐，不限制上一行，后面开始枚举时j中的1全表示坐上人了
        // 枚举第i行的坐法，第i行的合法坐法是没有相邻的1，这可以通过(j & (j >> 1)) == 0检测
        // 由于可用位置记为1，现在state是表示本行没坐人，只考虑了有坏座位的情况下，所以state是最大的情况
        for (int j = state; j > 0; j = (j - 1) & state) { // 每次j--后要& state才是下一个要尝试的状态
            if ((j & (j >> 1)) == 0) {
                // 现在j是第i行的状态，让为1的位代表有人坐上去，如何知道第i-1行的那个最大的开始枚举的state?
                // 用states[i - 1] & ~(j << 1 | j >> 1)，因为第i行的1会要求第i-1行左右位置不能为1
                int previousRowInitState = states[i - 1] & ~(j << 1 | j >> 1);
                ans = max(ans, dfs(i - 1, previousRowInitState, states, memo) + __builtin_popcount(j)); // __builtin_popcount()统计二进制位中1的个数，对应的Java方法是Integer.bitCount()
            }
        }
        memo[i][state] = ans;
        return ans;
    }

    // 灵茶山艾府题解解法三，改成自底向上dp
    int maxStudents_implementation3(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> states(m); // state[i]表示一开始第i行的座位状态，位为1表示那个位置座位可用
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') {
                    states[i] |= 1 << (n - 1 - j);
                }
            }
        }
        vector<vector<int>> dp(m, vector<int>(1 << n, 0)); // dp[i][j]表示第i行初始座位状态为j的情况下[0, i]行的最大可坐人数
        // 贪心求第一行对应状态的最大可坐人数
        for (int j = states[0]; j > 0; j = (j - 1) & states[0]) {
            int x = j;
            int count = 0;
            while (x != 0) {
                int lowbit = x & -x;
                count++;
                x = x & ~(lowbit + (lowbit << 1));
            }
            dp[0][j] = count;
        }
        for (int i = 1; i < m; i++) {
            for (int j = states[i]; j > 0; j = (j - 1) & states[i]) { // 现求第i行初始座位状态为j的最大容纳数
                dp[i][j] = dp[i - 1][states[i - 1]]; // 第i行一个人都不坐，不限制上一行，后面开始枚举时s中的1全表示坐上人了
                // 枚举第i行初始座位状态为j的所有合法坐法
                for (int s = j; s > 0; s = (s - 1) & j) {
                    if ((s & (s >> 1)) == 0) { // 没有连续的1
                        int previousRowInitState = states[i - 1] & ~(s << 1 | s >> 1); // 上一行的合法初始状态
                        dp[i][j] = max(dp[i][j], dp[i - 1][previousRowInitState] + __builtin_popcount(s));
                    }
                }
            }
            dp[i][0] = dp[i - 1][states[i - 1]];
        }
        return dp[m - 1][states[m - 1]];
    }

    // 用`AcWing292. 炮兵阵地`的思路写，要清晰一些
    int maxStudents_implementation4(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> g(m); // state[i]表示一开始第i行的座位状态，位为1表示那个位置座位可用
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') {
                    g[i] |= 1 << (n - 1 - j);
                }
            }
        }
        vector<int> states; // 预处理求出无左右相邻1的状态
        for (int i = 0; i < 1 << n; i++) {
            if ((i & (i >> 1)) == 0) {
                states.push_back(i);
            }
        }
        // dp[i][j]表示当第i行的状态为j时，前i行的最大可坐数，用滚动数组优化
        vector<vector<int>> dp(2, vector<int>(1 << n));
        for (int i = 0; i < m; i++) {
            for (int j : states) { // 第i行状态
                if ((j & g[i]) != j) continue; // 若j非g[i]的子集，直接剪枝
                for (int k : states) { // 第i - 1行状态
                    if (i - 1 >= 0 && (k & g[i - 1]) != k) continue; // 剪枝
                    if (((j << 1) & k) == 0 && ((j >> 1) & k) == 0) {
                        dp[i & 1][j] = max(dp[i & 1][j], dp[(i - 1) & 1][k] + __builtin_popcount(j));
                    }
                }
            }
        }
        int ans = INT_MIN;
        for (int j : states) {
            ans = max(ans, dp[(m - 1) & 1][j]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1349 solu;
    vector<vector<char>> seats = {
        {'#','.','.','.','#'}, 
        {'.','#','.','#','.'}, 
        {'.','.','#','.','.'}, 
        {'.','#','.','#','.'}, 
        {'#','.','.','.','#'}};
    cout << solu.maxStudents(seats) << endl;
    cout << solu.maxStudents_implementation2(seats) << endl;
    cout << solu.maxStudents_implementation3(seats) << endl;
    vector<vector<char>> seats2 = {{'#','#','.'},{'#','.','.'},{'.','.','#'}};
    cout << solu.maxStudents_implementation3(seats2) << endl;
    cout << solu.maxStudents_implementation4(seats2) << endl;
    return 0;
}

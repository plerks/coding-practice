/*
url: https://leetcode.cn/problems/count-submatrices-with-all-ones/
相关: LeetCode85. 最大矩形, LeetCode1277. 统计全为 1 的正方形子矩阵
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1504 {
public:
    // 时间复杂度O(m^2 * n)
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> f(m, vector<int>(n)); // (i, j)往左连续1的数量
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    cnt = 0;
                    f[i][j] = 0;
                }
                else {
                    cnt++;
                    f[i][j] = cnt;
                }
            }
        }

        /* 计数不重不漏的方式是，以(i, j)为右下角，计数有多少个矩形。考虑的是最深层次的点

        注意不能：枚举竖线。然后求紧贴右边竖线的情况下，以f[i][j]为下边界 + 以f[i][j]为上边界 - 只有f[i][j]一条柱子。
        这样有重复，比如俩个竖着的1，以第一个1为上边界，以第二个1为下边界，会重复计数。这种方式考虑的是边
        */
        
        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 以(i, j)为右下角
                int w = INT_MAX;
                for (int k = i; k >= 0; k--) {
                    if (f[k][j] == 0) break;
                    w = min(w, f[k][j]); // 求上边界为k，下边界为i，能取的宽度是多少，这个宽度就是以[k, i]为高度的情况下，能有的矩形数
                    ans += w;
                }
            }
        }
        return ans;
    }

    /* 参考官方题解，用单调栈优化。
    虽然是参考官方题解，不过由于官方题解讲得不清楚，所以理解之后的思路和官方题解不一样。

    按列来遍历，以(i, j)位置为右下角能有多少种方案？
    考虑(i - 1, j)位置，如果 f[i - 1][j] <= f[i][j]，那么(i - 1, j)的方案(i, j)全都能接受，
    对应方案只需要把右下角往下拉到(i, j)就行了。所以，我们要找第一个f[x][j] <= f[i][j]的行号x (x < i)。
    这可以通过单调栈来完成，同时，我们还需知道(x, j)位置的方案数，所以单调栈要存个pair。
    
    然后，行(x, i]之间还有一些方案，(x, i)之间的 f 都大于 f[i][j]，1的向左宽度都 > f[i][j]，所以方案数为 w * h = f[i][j] * (i - x)。
    
    把 part1 和 part2 加起来即为以(i, j)为右下角的方案数。

    边界情况：第一个f[x][j] <= f[i][j]的行号可能为-1

    时间复杂度O(mn)
    */
    int numSubmat_implementation2(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> f(m, vector<int>(n)); // (i, j)往左连续1的数量
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    cnt = 0;
                    f[i][j] = 0;
                }
                else {
                    cnt++;
                    f[i][j] = cnt;
                }
            }
        }

        int ans = 0;

        for (int j = 0; j < n; j++) {
            stack<pair<int, int>> st; // (行号, 方案数)
            for (int i = 0; i < m; i++) {
                while (!st.empty() && f[st.top().first][j] > f[i][j]) {
                    st.pop();
                }
                int cur = 0; // 当前第i行有多少种方案
                if (st.empty()) { // 第一个f[x][j] <= f[i][j]的行号为-1
                    cur = f[i][j] * (i + 1);
                }
                else {
                    cur = f[i][j] * (i - st.top().first) + st.top().second;
                }
                ans += cur;
                st.push({i, cur});
            }
        }
        return ans;
    }

    /* numSubmat_implementation2()之后，重新来看官方题解原本的思路。
    如何求以(i, j)为右下角的方案数？
    当前已知以上面的点为右下角的方案数。f[x][j] <= f[i][j] 的话，方案可以完全接收，把右下角往下拉就行。
    但是如果 f[x][j] > f[i][j] 的话就不一样了，需要裁剪一部分。
    以(i, j)为右下角的方案是一个个矩形，其中不乏像 mat = [[0,0,1],[0,1,1],[1,1,1],[0,0,1]] 的(2, 2)位置一样，方案并集非矩形，而是
    一个不规则的图形的情况，f[3][2]的长度在一个不规则的位置，会不会很难处理？不会

    对(i, j)使用单调栈找第一个f[x][j] <= f[i][j]的行号会出栈一些元素，出栈的行
    r
    .
    .
    .
    q
    .
    .
    .
    p
    的f[_][j]从下往上单减，而 f[(p, q)][j] 都是大于 f[p][j] 的，
    所以，我们只需知道p往上在遇到第一个比自己短的q之前能长多高就行了。这部分 (f[p][j] - f[i][j]) * h 的右下角拉不下来，剪掉

    剪掉之后的为继承下来的方案数，再加上f[i][j]这个单行新增的方案数就是(i, j)的总方案数了

    时间复杂度O(mn)
    */
    int numSubmat_implementation3(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> f(m, vector<int>(n)); // (i, j)往左连续1的数量
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    cnt = 0;
                    f[i][j] = 0;
                }
                else {
                    cnt++;
                    f[i][j] = cnt;
                }
            }
        }

        int ans = 0;

        for (int j = 0; j < n; j++) {
            stack<int> st; // 行号
            int cur = 0; // 当前位置的方案数，用来求下一个位置的方案数
            for (int i = 0; i < m; i++) {
                while (!st.empty() && f[st.top()][j] > f[i][j]) {
                    int p = st.top(); st.pop();
                    int q = st.empty() ? -1 : st.top();
                    int h = p - q; // (q, p]
                    cur -= (f[p][j] - f[i][j]) * h;
                }
                cur += f[i][j]; // 加上第i行，高度为1的方案数
                ans += cur;
                st.push(i);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1504 solu;
    // cout << solu.numSubmat(*new vector<vector<int>>{{1,0,1},{1,1,0},{1,1,0}}) << endl;
    // cout << solu.numSubmat(*new vector<vector<int>>{{0,1,1,0},{0,1,1,1},{1,1,1,0}}) << endl;

    // cout << solu.numSubmat_implementation2(*new vector<vector<int>>{{1,0,1},{1,1,0},{1,1,0}}) << endl;
    // cout << solu.numSubmat_implementation2(*new vector<vector<int>>{{0,1,1,0},{0,1,1,1},{1,1,1,0}}) << endl;
    // cout << solu.numSubmat_implementation2(*new vector<vector<int>>{{1,1,1,1,0},{1,0,0,1,0},{0,0,1,0,1},{0,1,0,0,0}}) << endl;
    cout << solu.numSubmat_implementation2(*new vector<vector<int>>{{0,0,0},{0,0,0},{0,1,1},{1,1,0},{0,1,1}}) << endl;

    cout << solu.numSubmat_implementation3(*new vector<vector<int>>{{0,0,0},{0,0,0},{0,1,1},{1,1,0},{0,1,1}}) << endl;
    return 0;
}
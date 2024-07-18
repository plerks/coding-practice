/*
url: https://leetcode.cn/problems/count-the-number-of-inversions/description/
参考: https://www.bilibili.com/video/BV17w4m1e7Nw/
      https://leetcode.cn/problems/count-the-number-of-inversions/solutions/2819143/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-974t/
标签: LeetCode第133场双周赛, 逆序对
*/

#include <bits/stdc++.h>

using namespace std;

// 这次双周赛3题

class Solution3193 {
public:
    // 灵茶山艾府题解解法一，记忆化搜索
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        const int MOD = 1e9 + 7;
        vector<int> req(n, -1); // req[i]表示prem[0, i]要求的逆序对个数
        for (auto v : requirements) {
            req[v[0]] = v[1];
        }

        int m = *max_element(req.begin(), req.end());

        vector<vector<int>> memo(n, vector<int>(m + 1, -1));

        // dfs(i, j)表示[0, i]有j个逆序对的排列种数。从右往左填值
        function<int(int, int)> dfs = [&](int i, int j) {
            if (i == 0) return j == 0 ? 1 : 0;
            if (memo[i][j] != -1) return memo[i][j];

            int res = 0;
            /* 完全不用知道现在剩下的数具体是多少，只需要知道它们有一个相对的大小顺序，知道
            它们是第几大，就可以知道它会与前面的数产生的逆序对个数。
            */
            /* 现在还有i + 1个数可用，它们有个相对的大小顺序，每个数有k个比自己大的数(k从0到i)，这k个数后面会填在前面与当前这个数构成逆序，
            直接就能确定逆序对的个数。注意这里相当于是把逆序对记在右边界位置，不要来回算了两次。 */

            // 注意这里的关键点，完全不知道具体的数是多少，就可以计算会有的逆序对数

            /* 对于requirements的要求，在i位置可以产生的逆序对个数为[0, i]，若i - 1位置有要求[0, i - 1]的逆序对个数必须是r，
            要让[0, i]总的逆序对个数是j，则i位置产生的逆序对个数必须为j - r，也就是必须把从右往左数第j - r个数放在i位置(下标为i-(j-r))
            这就有范围要求，必须i-(j-r) >= 0，否则达成不了，dfs(i, j)只能为0
            */
            int r = req[i - 1];
            if (r != -1) { // 有要求，[0, i - 1]的逆序对个数必须为r，则在i位置必须挑特定大小的数
                if (j - r >= 0 && (i - (j - r)) >= 0) {
                    res = dfs(i - 1, r);
                }
                else res = 0;
            }
            else { // 无要求，则i位置枚举放各个大小的数
                for (int k = 0; k <= i && j - k >= 0; k++) {
                    res = (res + dfs(i - 1, j - k)) % MOD;
                }
            }

            memo[i][j] = res;
            return res;
        };

        return dfs(n - 1, req[n - 1]); // 输入保证至少有一个i满足endi == n - 1
    }

    // 灵茶山艾府题解解法二，改成递归
    int numberOfPermutations_implementation2(int n, vector<vector<int>>& requirements) {
        const int MOD = 1e9 + 7;
        vector<int> req(n, -1); // req[i]表示prem[0, i]要求的逆序对个数
        for (auto v : requirements) {
            req[v[0]] = v[1];
        }

        int m = *max_element(req.begin(), req.end());
        // f[i][j]表示[0, i]有j个逆序对的方案数
        vector<vector<int>> f(n, vector<int>(m + 1, 0));
        f[0][0] = 1; // 注意这里不需要考虑选哪个放在0位置，记忆化搜索的代码要好理解一些
        /* 若i - 1有要求r，则f[i][j] = f[i - 1][j - r];
           若i - 1没有要求，则f[i][j] = Σf[i - 1][j - k]; 这个求和可以用前缀和优化
        */
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m + 1; j++) {
                int r = req[i - 1];
                if (r != -1) { // 有要求，i位置要填的数固定
                    if (j - r >= 0 && j - r <= i) {
                        f[i][j] = f[i - 1][r];
                    }
                }
                else {
                    for (int k = 0; k <= i && j - k >= 0; k++) {
                        f[i][j] = (f[i][j] + f[i - 1][j - k]) % MOD;
                    }
                }
            }
        }
        return f[n - 1][req[n - 1]];
    }
};

int main(int argc, char const *argv[]) {
    Solution3193 solu;
    /* vector<vector<int>> requirements = {{2,2},{0,1}};
    cout << solu.numberOfPermutations(3, requirements) << endl; */
    vector<vector<int>> requirements2 = {{2,0}};
    cout << solu.numberOfPermutations(3, requirements2) << endl;
    cout << solu.numberOfPermutations_implementation2(3, requirements2) << endl;
    return 0;
}

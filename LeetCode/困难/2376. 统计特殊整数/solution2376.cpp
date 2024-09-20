/*
url: https://leetcode.cn/problems/count-special-integers/description/?envType=daily-question&envId=2024-09-20
参考: https://leetcode.cn/problems/count-special-integers/solutions/2916434/tong-ji-te-shu-zheng-shu-by-leetcode-sol-7qai/
标签: 数位dp
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2376 {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int len = s.size();
        vector<vector<int>> memo(len, vector<int>(1 << 10, -1));

        // i表示现在填到哪一位了，mask表示已经用了的数字，isLimit表示前面填的数字是否与n相同，isNum表示已填的数字是否有非0
        auto dfs = [&](auto &dfs, int i, int mask, bool isLimit, bool isNum) -> int {
            if (i == len) return isNum; // 若isNum为false，说明全为0，不合法，返回0，否则得到了一个合法数字
            if (!isLimit && isNum && memo[i][mask] != -1) return memo[i][mask];
            int res = 0;
            if (!isNum) { // 前面填的数字都是0，则这一位也可以填0，i位置还不是填出的数字的首位
                res += dfs(dfs, i + 1, mask, false, false);
            }
            // i位置要填数字，如果前面还全是0，则这位置不能填0，否则是枚举了一个有前导0的数，要从1开始，若前面不全为0，则从0开始枚举
            // 前面全是0，当前位置从1到s[i]
            // 前面已经有了非0的数字，当前位置能枚举的范围和前面是否和n相同有关，若不同能枚举0-9，否则只能到s[i](因为枚举的数不能超过n)
            int lo = isNum ? 0 : 1;
            int hi = isLimit ? s[i] - '0' : 9;
            for (int d = lo; d <= hi; d++) {
                if ((mask >> d & 1) == 0) {
                    res += dfs(dfs, i + 1, mask | (1 << d), isLimit && (d == hi), true);
                }
            }

            // 只需要记忆isLimit为false且isNum为true的情况，其它情况不会被再次计算(其它情况只会成为一次子问题)
            if (!isLimit && isNum) {
                memo[i][mask] = res;
            }

            return res;
        };
        
        return dfs(dfs, 0, 0, true, false);
    }
};

int main(int argc, char const *argv[]) {
    Solution2376 solu;
    cout << solu.countSpecialNumbers(403) << endl;
    return 0;
}

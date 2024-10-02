/*
url: https://leetcode.cn/problems/minimum-cost-for-tickets/description/?envType=daily-question&envId=2024-10-01
参考: https://leetcode.cn/problems/minimum-cost-for-tickets/solutions/2936177/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-tkw4/
标签: 记忆化搜索, 动态规划例题, 滑动窗口
*/

#include <bits/stdc++.h>

using namespace std;

class Solution983 {
public:
    /* 灵茶山艾府题解解法一，这题直接想dp不好想 为了覆盖第i天而买的票可能覆盖i右边的日期 的问题，得先想记忆化搜索。
    */
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // 若某一天通行证还在生效，则不需要买新的通行证，于是通行证的作用时段是互斥的
        // dfs(i)表示覆盖第i天及右侧的最小开销
        // 若第i天非旅游日，只需覆盖i+1右边即可，dfs(i) = dfs(i + 1)
        // 若第i天是旅游日，注意，此时的dfs(i)是由更小的dfs(i-x)而来，i天一定不被dfs(i-x)覆盖才会递归
        unordered_set<int> set(days.begin(), days.end());
        int max = *max_element(days.begin(), days.end());
        vector<int> memo(max + 1, -1);

        auto dfs = [&](auto &dfs, int i) {
            if (i > max) return 0;
            if (memo[i] != -1) return memo[i];
            int res = 0;
            if (!set.count(i)) {
                res = dfs(dfs, i + 1);
            }
            else res = min(dfs(dfs, i + 1) + costs[0], min(dfs(dfs, i + 7) + costs[1], dfs(dfs, i + 30) + costs[2]));
            memo[i] = res;
            return res;
        };

        return dfs(dfs, 1);
    }

    /* 灵茶山艾府题解解法二，dp[i]表示覆盖前i天的最小开销，若第i天非旅游日，则只需覆盖前i - 1天，
    若第i天是旅游日，i一定被某张通行证覆盖，这里不知道i在通行证日期的哪个位置，但是，将i放在那张通行证
    的最后一天，则子问题更小，值也一定更小。 */
    int mincostTickets_implementation2(vector<int>& days, vector<int>& costs) {
        unordered_set<int> set(days.begin(), days.end());
        int max = days.back(); // 题目保证days从小到大排
        vector<int> dp(max + 1, 0);
        for (int i = 1; i <= max; i++) {
            if (!set.count(i)) dp[i] = dp[i - 1];
            else {
                dp[i] = min({dp[i - 1] + costs[0], dp[std::max(i - 7, 0)] + costs[1], dp[std::max(i - 30, 0)] + costs[2]});
            }
        }
        return dp[max];
    }

    // 换一个dp方向，改成和记忆化搜索的逆序一致
    int mincostTickets_implementation3(vector<int>& days, vector<int>& costs) {
        unordered_set<int> set(days.begin(), days.end());
        int max = days.back(); // 题目保证days从小到大排
        vector<int> dp(max + 2, 0);
        for (int i = max; i >= 1; i--) {
            if (!set.count(i)) dp[i] = dp[i + 1];
            else {
                dp[i] = min({dp[i + 1] + costs[0], dp[std::min(i + 7, max + 1)] + costs[1], dp[std::min(i + 30, max + 1)] + costs[2]});
            }
        }
        return dp[1];
    }

    /* 灵茶山艾府题解解法三，上面的解法和days元素的范围有关。当在days[i]分别买为期1，7，30天的票后，以7为例，
    需要知道的是days中最后一个 < days[i] - 6的位置j，然后完成days[1]到days[j]即可，而j是单调变大的，因此可以
    用一个全局的指针来记。
    */
    int mincostTickets_implementation4(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        int j = 0, k = 0; // j, k用来记录买为期7，30天的票的上一个位置，买为期为1天的票不用记录，因为最后一个不能覆盖的就是days[i - 1]
        // 想要完全前i个day，即完成买覆盖这个day的票后，找到对应的没被覆盖的day的最后位置
        vector<int> dp(n + 1);
        for (int i = 0; i < n; i++) {
            int day = days[i];
            while (days[j] < day - 6) {
                j++;
            }
            while (days[k] < day - 29) {
                k++;
            }
            // 循环结束后j - 1, k - 1分别是最后一个当前day不能涉及的位置，若为-1则表示全能涉及到，子问题的开销为0
            
            
            /* 本来应该是 dp[i] = min({dp[i - 1] + costs[0], dp[j - 1] + costs[1], dp[k - 1] + costs[2]});
            但这会出现-1索引，将填写位置整体右移1
            */
            dp[i + 1] = min({dp[i - 1 + 1] + costs[0], dp[j - 1 + 1] + costs[1], dp[k - 1 + 1] + costs[2]});
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution983 solu;
    vector<int> days = {1,4,6,7,8,20};
    vector<int> costs = {2,7,15};
    cout << solu.mincostTickets(days, costs) << endl;
    cout << solu.mincostTickets_implementation2(days, costs) << endl;
    cout << solu.mincostTickets_implementation3(days, costs) << endl;
    cout << solu.mincostTickets_implementation4(days, costs) << endl;
    return 0;
}

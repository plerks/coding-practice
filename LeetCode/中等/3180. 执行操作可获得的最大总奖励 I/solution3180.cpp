/*
url: https://leetcode.cn/problems/maximum-total-reward-using-operations-i/description/
参考: https://www.bilibili.com/video/BV1h7421R78s/
      https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/solutions/2805413/bitset-you-hua-0-1-bei-bao-by-endlessche-m1xn/
相关: LeetCode3181. 执行操作可获得的最大总奖励 II
标签: LeetCode第401场周赛, 0-1背包
*/

#include <bits/stdc++.h>

using namespace std;

// 此题与LeetCode3181. 执行操作可获得的最大总奖励 II相同，只是数据范围小些
class Solution3180 {
public:
    // 周赛时的解法，这题不能dp，因为最优解不一定由子最优解转移而来，所以想着应该要一定的暴力枚举，写了个记忆化搜索，577 / 586 个通过的测试用例，超时。
    int maxTotalReward_time_limit_exceeded(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        map<pair<int, int>, int> memo;
        int n = rewardValues.size();

        function<int(int, int)> dfs = [&](int start, int x) {
            if (memo.find(make_pair(start, x)) != memo.end()) {
                return memo[make_pair(start, x)];
            }
            int ans = 0;
            int left = start, right = n - 1;
            // 搜索rewardValues中第一个大于x的位置
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (rewardValues[mid] <= x) {
                    left = mid + 1;
                }
                else right = mid - 1;
            }
            for (int i = left; i < n; i++) {
                ans = max(ans, rewardValues[i] + dfs(i, x + rewardValues[i]));
            }
            memo[{start, x}] = ans;
            return ans;
        };
        
        return dfs(0, 0);
    }

    /* 参考灵茶山艾府题解。用0-1背包来做，用f[i][j]表示能否用前i个元素凑出j，则这是一个0-1背包问题。
    考虑选择顺序，最优解若不是按从小到大的顺序选的，则改成从小达大一定能选，不会违反限制，于是先将rewardValues排序，然后从小到大选。
    先证这样一个问题，当到了rewardValues[i]时，所选出的最大收益一定<2*rewardValues[i]。归纳证明，
    若不选rewardValues[i]，则成立，若选rewardValues[i]，则由归纳假设现在已经积累的x一定<2*rewardValues[i - 1]，i位置能选则已积累的
    值 < rewardValues[i]。
    选i位置之后总和 < x旧 + rewardValues[i] < 2*rewardValues[i]，也成立
    */
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        // 去重，相同的数只可能选一次，所以可以直接去重
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        int n = rewardValues.size();
        vector<bool> f(2 * rewardValues.back(), false); // 由前面的证明最优解 < 最大值的2倍
        f[0] = true;
        for (int i = 0; i < n; i++) {
            // 只需考虑选rewardValues[i]时，[rewardValues[i], 2 * rewardValues[i])是否能被凑出，若不选i位置，前面部分已经设置好了值，不用管，若选i位置，则总和一定在这个范围内
            for (int j = rewardValues[i]; j < 2 * rewardValues[i]; j++) {
                if (f[j - rewardValues[i]]) {
                    f[j] = true;
                }
            }
        }
        for (int j = 2 * rewardValues.back() - 1; j >= 0; j--) {
            if (f[j]) return j;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3180 solu;
    vector<int> rewardValues = {1,6,4,3,2};
    cout << solu.maxTotalReward(rewardValues) << endl;
    return 0;
}

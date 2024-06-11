/*
url: https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/description/
参考: https://www.bilibili.com/video/BV1h7421R78s/
      https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/solutions/2805413/bitset-you-hua-0-1-bei-bao-by-endlessche-m1xn/
相关: LeetCode3180. 执行操作可获得的最大总奖励 I
标签: LeetCode第401场周赛, 0-1背包, std::bitset
*/

// 这次周赛两题，第3题和第4题题目内容一样，但是第3题我写的那个比较暴力的记忆化搜索过不了

#include <bits/stdc++.h>

using namespace std;

// 此题与LeetCode3180. 执行操作可获得的最大总奖励 I相同，只是数据范围大些
class Solution3180 {
public:
    /* 参考灵茶山艾府题解。用0-1背包来做，用f[i][j]表示能否用前i个元素凑出j，则这是一个0-1背包问题。
    考虑选择顺序，最优解若不是按从小到大的顺序选的，则改成从小达大一定能选，不会违反限制，于是先将rewardValues排序，然后从小到大选。
    先证这样一个问题，当到了rewardValues[i]时，所选出的最大收益一定<2*rewardValues[i]。归纳证明，
    若不选rewardValues[i]，则成立，若选rewardValues[i]，则由归纳假设现在已经积累的x一定<2*rewardValues[i - 1]，i位置能选则已积累的
    值 < rewardValues[i]。
    选i位置之后总和 < x旧 + rewardValues[i] < 2*rewardValues[i]，也成立
    */
    // 这题数据范围变大，这样写能过LeetCode3180，不能过这题（572 / 580 个通过的测试用例），得用bitset
    int maxTotalReward_time_limit_exceeded(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        // 去重，相同的数只可能选一次，所以可以直接去重
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        int n = rewardValues.size();
        vector<bool> f(2 * rewardValues.back(), false);
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

    // 参考灵茶山艾府题解
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        int n = rewardValues.size();
        // 1 <= rewardValues.length <= 5 * 10^4，最优解不超过最大值的2倍，但是泛型里不能写2 * max，只能直接写100000
        bitset<100000> bitset; // 默认构造每一位都是false
        bitset.set(0, 1);
        // 看[rewardValues[i], 2 * rewardValues[i])的部分能否凑出，要取出当前[0, rewardValues[i])的部分再|，但要用把rewardValues[i]及更高的位置置为0的bitset来|
        for (int i = 0; i < n; i++) {
            int shift = bitset.size() - rewardValues[i];
            bitset |= (bitset << shift >> shift << rewardValues[i]); // 耗时848ms
            // 也可以写成bitset |= (bitset << shift >> (shift - rewardValues[i]))，耗时586ms
        }
        for (int j = rewardValues.back() * 2 - 1; j >= 0; j--) {
            if (bitset.test(j)) return j;
        }
        return -1;
    }

    /* 参考灵茶山艾府题解，题解中还提了2个优化。记m = max(rewardValues)，若存在m - 1，则{m-1, m}已达到上界2m-1，直接返回2m-1。
    若存在两个不同元素u, v之和为2m-1，则{u, v}也是可选且达到上界的，也返回2m-1，随机数据出现这种情况概率挺大。这样优化
    之后用时192ms
    */
    int maxTotalReward_implementation2(vector<int>& rewardValues) {
        int m = *max_element(rewardValues.begin(), rewardValues.end());

        unordered_set<int> set;

        for (int num : rewardValues) {
            if (set.count(num)) continue;
            if (num == m - 1 || set.count(2 * m - 1 - num)) return 2 * m - 1;
            set.insert(num);
        }

        sort(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        int n = rewardValues.size();
        // 1 <= rewardValues.length <= 5 * 10^4，最优解不超过最大值的2倍，但是泛型里不能写2 * max，只能直接写100000
        bitset<100000> bitset; // 默认构造每一位都是false
        bitset.set(0, 1);
        // 看[rewardValues[i], 2 * rewardValues[i])的部分能否凑出，要取出当前[0, rewardValues[i])的部分再|，但要用把rewardValues[i]及更高的位置置为0的bitset来|
        for (int i = 0; i < n; i++) {
            int shift = bitset.size() - rewardValues[i];
            bitset |= (bitset << shift >> (shift - rewardValues[i]));
        }
        for (int j = rewardValues.back() * 2 - 1; j >= 0; j--) {
            if (bitset.test(j)) return j;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3180 solu;
    vector<int> rewardValues = {1,6,4,3,2};
    cout << solu.maxTotalReward(rewardValues) << endl;
    cout << solu.maxTotalReward_implementation2(rewardValues) << endl;
    return 0;
}

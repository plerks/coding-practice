/*
url: https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/
参考: https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/solutions/2413344/tan-xin-by-endlesscheng-immn/
      https://www.bilibili.com/video/BV1Em4y1T7Bq/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2835 {
public:
    /* 参考灵茶题解，
    每次分总和不变，由于最细可以分成全是1，所以只要sum(nums) >= target，就可以凑出来target。
    从小到大考虑凑出target的每一位，
    这要用到这样一个结论：现在要凑 2^i（用nums中所有 <= 2^i 的元素），只要这些元素的和 >= 2^i，一定可以凑出来，
    这可以归纳证明，若可用元素有 2^i，则直接选即可，若没有，则所有元素 <= 2^(i - 1)，总和 >= 2^i，这可以凑出一个2^(i - 1)，
    剩下的一份的和也是 >= 2^(i - 1)的，所以可以出两个 2^(i - 1)，结论成立。

    由此引申的结论是，要凑 target[i, 0]，只要 <= 2^i 的元素的和 >= target[i, 0]，就可以凑出来。
    如果 target[i] == 0，不用考虑。
    如果target[i] == 1，若有2^i，问题变成 target[i - 1, 0]， s >= target[i - 1, 0]
    如果target[i] == 1，没有2^i，问题变成 问题变成先凑个 2^i，然后子问题 target[i - 1, 0]， s >= target[i - 1, 0]
    
    那么，一位位地遍历target，如果为0不用管，如果为1，且当前的和 <= target[i, 0] 就需要往高找，
    假设在target 2^i的位，发现 <= 2^i 的和不够，往上找找个最近的 2^j，2^j 一路分下来个 2^i，且分的过程会把
    2^(j - 1) 2^(j - 2) ... 2^i 全弄出来。所以只需跳到看 target[j, 0] 能否被凑出来
    */
    int minOperations(vector<int>& nums, int target) {
        if (accumulate(nums.begin(), nums.end(), 0LL) < target) return -1;
        int cnt[32]{};
        for (int x : nums) cnt[__lg(x)]++;
        int ans = 0;
        int i = 0;
        long long s = 0; // 当前 <= 2^i 的所有2的幂的总和
        while ((1LL << i) <= target) { // 要处理的target有效位
            s += (long long)cnt[i] * (1LL << i); // 或者直接 cnt[i] << i
            int mask = (1LL << (i + 1)) - 1;
            if (s < (target & mask)) {
                ans++; // 直接从i + 1开始找最近的1
                i++;
                while (cnt[i] == 0) {
                    i++;
                    ans++;
                }
            }
            else i++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2835 solu;
    // cout << solu.minOperations(*new vector<int>{1,2,8}, 7) << endl;
    // cout << solu.minOperations(*new vector<int>{1,32,1,2}, 12) << endl;
    cout << solu.minOperations(*new vector<int>{16,64,4,128}, 6) << endl;
    return 0;
}
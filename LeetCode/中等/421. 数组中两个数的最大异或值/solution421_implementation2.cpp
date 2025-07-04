/*
url: https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
参考: https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/solutions/2511644/tu-jie-jian-ji-gao-xiao-yi-tu-miao-dong-1427d/
相关: LeetCode2935. 找出强数对的最大异或值 II, LeetCode1803. 统计异或值在范围内的数对有多少
标签: 字典树, 异或, 哈希表
*/
#include <bits/stdc++.h>

using namespace std;

class Solution421 {
public:
    /* 灵茶题解不直接用字典树的解法，从高到低，一位一位地来构造ans，
    假设我们返现前面的位可以构造出 11101..，现在如何当前位能不能为1？
    nums中所有数x取前6位，? ^ (x & mask) == 111011..，则 ? = 111011.. ^ x，
    用一个哈希表存前面的 x & mask，找有无 111011.. ^ x 就能确认 ans 的这一位了。
    */
    int findMaximumXOR(vector<int>& nums) {
        const int HIGH_BIT = __lg(*max_element(nums.begin(), nums.end()));

        int mask = 0; // 用来取出前部的 [HIGH_BIT, i] 位
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            mask |= 1 << i;
            int attempt = ans | (1 << i); // 尝试ans这一位能不能为1
            unordered_set<int> seen;
            for (int x : nums) { // 枚举 (i, j) 里的右端点 j
                x &= mask;
                // (nums[i] ^ mask) ^ (nums[j] & mask) = attempt
                if (seen.count(attempt ^ x)) {
                    ans = attempt;
                    break; // 可以，直接尝试下一位了
                }
                seen.insert(x); // (nums[i] ^ mask)插入此轮的哈希表，作为 (i, j) 里的 i 备用。本来这题 (i, j) 的选择i j可以相等，应该在前面就insert，不过这种情况结果为0，无所谓
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution421 solu;
    cout << solu.findMaximumXOR(*new vector<int>{3,10,5,25,2,8}) << endl;
    return 0;
}
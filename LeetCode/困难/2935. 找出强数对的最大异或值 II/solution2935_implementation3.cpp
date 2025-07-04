/*
url: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/
参考: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/solutions/2523213/0-1-trie-hua-dong-chuang-kou-pythonjavac-gvv2/
相关: LeetCode421. 数组中两个数的最大异或值
标签: 【算法题单】位运算, 字典树, 滑窗
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2935 {
public:
    // 灵茶题解解法二，用哈希表的解法，和`LeetCode421. 数组中两个数的最大异或值`灵茶题解的哈希表解法一致。
    // 哈希表里要放当前[HIGH_BIT, i]的位的值以查找，不过为了检查 2 * x > y，还要记录前部为[HIGH_BIT, i]的最大值
    // 由于是按从小到大遍历的，前部相等，后面的数直接覆盖前面的就行
    int maximumStrongPairXor(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        const int HIGH_BIT = 19;
        int mask = 0; 
        for (int i = HIGH_BIT; i >= 0; i--) {
            mask |= 1 << i;
            int attempt = ans | (1 << i);
            // (x & mask) ^ (y & mask) == attempt
            unordered_map<int, int> seen; // (前面部分的位，整体的值)
            for (int y : nums) {
                int x_masked = attempt ^ (y & mask);
                if (seen.count(x_masked) && seen[x_masked] * 2 >= y) {
                    ans = attempt;
                    break;
                }
                seen[y & mask] = y;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2935 solu;
    cout << solu.maximumStrongPairXor(*new vector<int>{1,2,3,4,5}) << endl;
    cout << solu.maximumStrongPairXor(*new vector<int>{10, 100}) << endl;
    return 0;
}
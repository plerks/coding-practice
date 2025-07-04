/*
url: https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
相关: LeetCode2935. 找出强数对的最大异或值 II, LeetCode1803. 统计异或值在范围内的数对有多少
标签: 字典树, 异或
*/
#include <bits/stdc++.h>

using namespace std;

struct Trie {
    static const int HIGH_BIT = 30; // nums[i] <= 2^31 - 1
    array<Trie*, 2> child = {nullptr, nullptr};

    // 插入节点
    void insert(int x) {
        Trie* cur = this;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (cur->child[bit] == nullptr) {
                cur->child[bit] = new Trie();
            }
            cur = cur->child[bit];
        }
    }

    // 找与x异或的最大值
    int get_max_xor(int x) {
        Trie* cur = this;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            // ? ^ bit = 1，则 ? = bit ^ 1
            if (cur->child[bit ^ 1]) {
                ans |= 1 << i;
                cur = cur->child[bit ^ 1];
            }
            else if (cur->child[bit ^ 0]) {
                cur = cur->child[bit ^ 0];
            }
        }
        return ans;
    }
};

class Solution421 {
public:
    // 字典树的解法
    int findMaximumXOR(vector<int>& nums) {
        Trie trie;
        int ans = 0;
        for (int x : nums) {
            // 此题0 ≤ i ≤ j < n，i, j可以相等，直接先把nums[i]加进去，然后借助字典树找^值最大的路径
            // 借助字典树，每次尽量找^值为1的路径，这样就能顺着树高找到最大值，而不用和前面的所有数都^计算一遍。
            trie.insert(x);
            ans = max(ans, trie.get_max_xor(x));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution421 solu;
    cout << solu.findMaximumXOR(*new vector<int>{3,10,5,25,2,8}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/
参考: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/solutions/2523213/0-1-trie-hua-dong-chuang-kou-pythonjavac-gvv2/comments/2406838/
相关: LeetCode421. 数组中两个数的最大异或值
标签: 【算法题单】位运算, 字典树, 滑窗
*/
#include <bits/stdc++.h>

using namespace std;

// 灵茶题解评论区的一个解法，不用删除过小的节点，而是记录子树的最大值，这样就能把过小的x排除掉了

const int HIGH_BIT = 19; // nums[i] <= 2^20 - 1

struct Trie {
    array<Trie*, 2> child = {nullptr, nullptr};
    int mx = 0; // 子树的最大值

    void insert(int x) {
        Trie* cur = this;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (cur->child[bit] == nullptr) {
                cur->child[bit] = new Trie();
            }
            cur = cur->child[bit];
            cur->mx = x; // 由于此题从小到大遍历nums，这里不用 cur->mx = max(cur->mx, x)，x就是最大值
        }
    }

    // 找与x异或的最大值
    int get_max_xor(int x) {
        Trie* cur = this;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            // ? ^ bit = 1，则 ? = bit ^ 1
            if (cur->child[bit ^ 1] && cur->child[bit ^ 1]->mx * 2 >= x) {
                ans |= 1 << i;
                cur = cur->child[bit ^ 1];
            }
            else if (cur->child[bit ^ 0] && cur->child[bit ^ 0]->mx * 2 >= x) {
                cur = cur->child[bit ^ 0];
            }
        }
        return ans;
    }
};

class Solution2935 {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        Trie trie;
        for (int r = 0; r < nums.size(); r++) {
            ans = max(ans, trie.get_max_xor(nums[r]));
            trie.insert(nums[r]);
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
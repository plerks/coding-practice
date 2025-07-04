/*
url: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/
参考: https://leetcode.cn/problems/maximum-strong-pair-xor-ii/solutions/2523213/0-1-trie-hua-dong-chuang-kou-pythonjavac-gvv2/
相关: LeetCode421. 数组中两个数的最大异或值
标签: 【算法题单】位运算, 字典树, 滑窗
*/
#include <bits/stdc++.h>

using namespace std;

const int HIGH_BIT = 19; // nums[i] <= 2^20 - 1

struct Trie {
    array<Trie*, 2> child = {nullptr, nullptr};
    int cnt = 0; // 子树叶节点数，这里相当于懒惰删除标记，cnt == 0代表删除

    void insert(int x) {
        Trie* cur = this;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (cur->child[bit] == nullptr) {
                cur->child[bit] = new Trie();
            }
            cur = cur->child[bit];
            cur->cnt++;
        }
    }

    // 只改了cnt，并未真正删除节点。假定x在树中
    void remove(int x) {
        Trie* cur = this;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            cur->child[bit]->cnt--;
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
            if (cur->child[bit ^ 1] && cur->child[bit ^ 1]->cnt) {
                ans |= 1 << i;
                cur = cur->child[bit ^ 1];
            }
            else if (cur->child[bit ^ 0] && cur->child[bit ^ 0]->cnt) { // bit ^ 0 等于 bit，可以直接写bit，不过这样写清晰一点。
                cur = cur->child[bit ^ 0];
            }
        }
        return ans;
    }
};

class Solution2935 {
public:
    /* 灵茶题解解法一，这题的基础版是`LeetCode421. 数组中两个数的最大异或值`，用字典树来找最大的异或值。
    不过这题多加了个|x - y| <= min(x, y)的限制，先排序以保证 x < y，然后滑窗，把过小的x从字典树里删除
    */
    int maximumStrongPairXor(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        Trie trie;
        for (int l = 0, r = 0; r < nums.size(); r++) {
            while (nums[r] - nums[l] > nums[l]) {
                trie.remove(nums[l]);
                l++;
            }
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
/*
url: https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/
参考: https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/solutions/2044651/tong-ji-yi-huo-zhi-zai-fan-wei-nei-de-sh-cu18/
标签: 【算法题单】位运算, 字典树
*/

// 这篇题解，卡常仙人，C++使用avx2指令集，O(n^2)的复杂度，能和字典树解法差不多快：
// <https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/solutions/672266/bao-li-aczen-yao-neng-shao-de-liao-cni-b-j2co/>

#include <bits/stdc++.h>

using namespace std;

static constexpr int HIGH_BIT = 14; // 最高有效位是1 << 14

struct Trie {
    array<Trie*, 2> child{nullptr, nullptr}; // 左右儿子
    int sum; // 子树叶节点的个数
    
    Trie(): sum(0) {}

    // 增加一个数字，把其0-1路径构造出来
    void add(int x) {
        Trie* cur = this;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (cur->child[bit] == nullptr) {
                cur->child[bit] = new Trie();
            }
            cur = cur->child[bit];
            cur->sum++; // 注意当前节点的 0/1儿子 才代表存了 0/1。也就是说 0/1 在 parent -> child 的边上
        }
    }

    // 计算 ^ num <= x 的叶节点数目
    int calc(int num, int x) {
        Trie* cur = this;
        int sum = 0; // 合法叶子数目
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (num >> i) & 1; // 关心的是 节点 ^ bit 的值
            if ((x >> i) & 1) { // x 这一位为 1
                if (cur->child[bit ^ 0] != nullptr) { // 走 bit ^ 0 分支，(bit ^ 0) ^ bit 结果一定为0，<= x 的 1，全累加，bit ^ 0 可以简写为 bit
                    sum += cur->child[bit ^ 0]->sum;
                }
                if (cur->child[bit ^ 1] == nullptr) {
                    return sum;
                }
                else cur = cur->child[bit ^ 1]; // bit ^ 1 为与 num 异或结果为 1 的分支，进去继续找
            }
            else { // x 这一位为 0，只需递归“左子树”(异或值为0的方向)
                if (cur->child[bit ^ 0] == nullptr) {
                    return sum;
                }
                else {
                    cur = cur->child[bit ^ 0];
                }
            }
        }
        sum += cur->sum; // cur最后指向叶子节点，比如节点异或值和x都是1，没有后续的位需要判断了，相等，加上
        return sum;
    }
};

class Solution1803 {
public:
    /* 参考官方题解。
    枚举j为右边界，枚举左边界计算，O(n^2)会超时，对于一个j，如何快速求出左侧所有nums[i] ^ nums[j] <= x的i的个数？
    将nums的所有数字补0，1 <= nums[i] <= 2 * 10^4 < 2^15，所以最高有效位在2^14的位置。
    补0使得位数相等，这样字典序就能用来判断大小，按位异或的结果就可以判断与x的大小关系。构造字典树，字典树的每个叶子代表nums的一个数字。
    如何求 异或 ^ nums[j] <= x 的个数？如果直接模拟，找出所有叶子，需要O(n)时间。
    这里的技巧很像线段树的懒惰标记。在字典树每个节点上记录这样一个字段 sum：以根结点到该节点路径为前缀的数目，也即这个节点所代表的子树，下面有
    多少个数字(多少个叶节点)！
    现在前面数字的字典序已经放进字典树了，字典树中不包含异或的概念，单纯是0-1路径结构，
    以nums[j]为右端点，要求异或结果 <= x 时，字典树中有nums[0, j)，按位来异或，如果 cur ^ nums[j] 为 0 且 x 为 1，
    说明子树所有叶节点^nums[j]这一位上全为0，而 x 这位为1，则 sum 个节点全部都是 <= x 的，不用再考虑其它分支。
    若为 0 0 ，只需遍历左子树
    若为 1 0 ，没有合法的
    若为 1 1 ，则加上左子树的sum + 遍历右子树

    根节点没存值，这样不好操作。换一种分类方式，如果 x 为 1，左子树全家，递归右子树
    如果 x 为0，递归左子树

    就和懒惰标记的线段树一样，每层最多访问两个节点。时间复杂度为树高。

    再强调一下，字典树存了nums[0, j)的字典序，没有异或的成分。拿 nums[j] 在字典树上走，找 异或结果 <= x 的数量。
    由于补了前导0，每个叶子都在同一层，要找的是x左边的叶子的数量。

    此外由于是边建树边计算的，两次f()要建2棵字典树。似乎也可以直接先建一棵完整的，不过要考虑(i, j) (j, i) (j, j)重复计数的问题。

    时间复杂度 O(nlogU)，U为数据范围。n, nums[i], low, high 都是2e4的级别。
    */
    int countPairs(vector<int>& nums, int low, int high) {
        return f(nums, high) - f(nums, low - 1);
    }

    // 求 nums[i] ^ nums[j] <= x 的所有 (i, j) 数目
    int f(vector<int>& nums, int x) {
        Trie* root = new Trie();
        int res = 0;
        for (int j = 1; j < nums.size(); j++) { // 枚举右端点
            root->add(nums[j - 1]);
            res += root->calc(nums[j], x);
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution1803 solu;
    cout << solu.countPairs(*new vector<int>{1,4,2,7}, 2, 6) << endl;
    return 0;
}
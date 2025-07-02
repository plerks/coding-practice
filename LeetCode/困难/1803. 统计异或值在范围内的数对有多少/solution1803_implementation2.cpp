/*
url: https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/
参考: https://leetcode.cn/problems/count-pairs-with-xor-in-a-range/solutions/2045560/bu-hui-zi-dian-shu-zhi-yong-ha-xi-biao-y-p2pu/
标签: 【算法题单】位运算
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1803 {
public:
    /* 灵茶题解解法，算是字典树的从底而上的过程，只用哈希表就完成了。
    如何求 异或值 < x 的(i, j)对数？(0 <= i, j < n)
    先考虑这个问题，两个数a, b， a < b 是如何产生的？
    将二者补前导0变成长度相等，那么若 a < b，等价于 a 的字典序 < b 的字典序，
    等价于 a, b 刚开始有一段长度相等，然后到了第一个不同的数字就分出了大小关系，a在这一位上的bit < b在这一位上的bit 。
    
    求 异或 < x 的方案数，我们枚举确认了二者大小关系的那个bit所在的位置！
    例如，假设确认 ? < x 发生在第0号比特，那么首先x的这一位必须是1，否则跳过，且 ? 一定为 x - 1（前面的比特要相同）
    如何求 nums[i] ^ nums[j] == x - 1 的方案数？这个简单，用哈希表，枚举 nums[i] ，求 nums[j] == (x - 1) ^ nums[i] 的个数即可。
    这样，我们就找到了在0号比特位确认了 < x 的方案数。
    
    然后把处理过的位右移挪掉，枚举下一个确认二者大小的比特位置即可。

    重复计数问题
    上面枚举的 (i, j) 没有判断 i > j，也没有判断 i == j 的情况，{ < high + 1 } - { < low } ，二者都会包含所有 (i, i) 的情况，会消掉，
    最终方案里不会包含 (i, i) 这种非法方案。所以只需 ans / 2 去掉 i, j 交换的重复计数即可。

    时间复杂度 O(nlogU)，U为数据范围。
    */
    int countPairs(vector<int>& nums, int low, int high) {
        // 求 { < high - 1 } - { < low }，最后 / 2
        unordered_map<int, int> map;
        for (int &num : nums) map[num]++;
        high++;
        int ans = 0;
        // 计算 { < high - 1 } 和 { < low } 可以一起进行
        for (; high > 0; low >>= 1, high >>= 1) {
            unordered_map<int, int> nxt;
            for (auto [x, c] : map) { // 枚举 nums[i]，求 nums[j] == (x - 1) ^ nums[i] 的个数
                if (high & 1 && map.count(x ^ (high - 1))) ans += c * map[x ^ (high - 1)];
                if (low & 1 && map.count(x ^ (low - 1))) ans -= c * map[x ^ (low - 1)];
                nxt[x >> 1] += c;
            }
            map = std::move(nxt);
        }
        return ans / 2;
    }
};

int main(int argc, char const *argv[]) {
    Solution1803 solu;
    cout << solu.countPairs(*new vector<int>{1,4,2,7}, 2, 6) << endl;
    // cout << solu.countPairs(*new vector<int>{1}, 1, 6) << endl;
    return 0;
}
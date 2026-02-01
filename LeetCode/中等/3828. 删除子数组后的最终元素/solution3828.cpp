/*
url: https://leetcode.cn/problems/final-element-after-subarray-deletions/
标签: LeetCode第487场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3828 {
public:
    /* 参考灵茶和TsReaper题解。
    以 nums = [1, 6, 3, 5] 为例，Alice 能否保留 6 到最后？
    如果 Alice 选择删 6 左右的某个子数组，比如删 3 ，Bob 可以立刻删 [6, 5] ，这样就只留一个 [1] ，然后就结束了。
    这不如 Alice 最开始直接删 [1, 6, 3] ，然后变成剩 [5] 。

    也就是说，如果中间某个数大，且 Alice 想留，一定是留不下来的，Bob 会立刻删得只剩两边更小的那个元素，Bob 如果不这么干， 想着
    中间有元素更小，自己留一留，下回合 Alice 也会做同样的事。

    因此 Alice 在第一回合选择两边更大的那个元素留下，其它全删除，就是最终的结果。

    例如，nums = [1, 6, 0, 5]，Alice 第一回合删成 [6, 0, 5] 以期待 Bob 下回合没做操作，然后自己再下回合删成 [6]，但是到了
    Bob 的回合，他会删成 [0, 5] 以期待追求 0，但是 Alice 下回合会删成 [5]。虽然没一回合结束，但是也是相同的结果。

    可以证明答案是 max(nums[0], nums[n - 1])，
    1. 采用上述策略，可以取到 max(nums[0], nums[n - 1])，因此答案 >= max(nums[0], nums[n - 1])
    2. 如果最后留下的数 > max(nums[0], nums[n - 1])，
        Alice 第一轮操作后，如果 max(nums[0], nums[n - 1]) 没被删掉，比如变成 [6, 3, 5]，那么 Bob 知道不能追求中间的更小值 3，
        否则 Alice 能在下回合删成 [6]，所以 Bob 会直接把数组删成 [5]，也就是说，Alice 在第一回合的先手是有完全决定权的，直接删成只剩 max(nums[0], nums[n - 1])，
        若 Alice 不首回合杀，决定权会到 Bob 手里，Alice 不会这样做。
    */
    int finalElement(vector<int>& nums) {
        return max(nums.front(), nums.back());
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
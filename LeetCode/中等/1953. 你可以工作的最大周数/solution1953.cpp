/*
url: https://leetcode.cn/problems/maximum-number-of-weeks-for-which-you-can-work/description/
参考: https://leetcode.cn/problems/maximum-number-of-weeks-for-which-you-can-work/solutions/908442/ni-ke-yi-gong-zuo-de-zui-da-zhou-shu-by-rbidw/
      https://www.bilibili.com/video/BV1Nf421U7em/
相关: LeetCode3139. 使数组中所有元素相等的最小开销
标签: 贪心, 构造, 数学
*/

#include <bits/stdc++.h>

using namespace std;

// 此题在`LeetCode3139. 使数组中所有元素相等的最小开销`中有使用
class Solution1953 {
public:
    /* 参考灵茶山艾府在LeetCode3139中的视频讲解，此题相当于nums[i]代表有i号盒子有nums[i]个小球，
    每次选一个盒子取出一个球然后从左到右摆放，不能相邻两次从同一个盒子取球。
    以longest表示nums中的最大值，rest表示sum(nums)-max(nums)，也就是其它盒子的小球总数。
    官方题解证明的关键结论是:
        可以完成所有工作的充要条件是: longest <= rest + 1
    先证必要性（通过证明逆否证明），若longest > rest + 1，这时longest占总小球数超过半数，所以
    longest对应的盒子的小球一定会放相邻。
    例如，nums = {4,1,1}，此时有total = longest + rest = 4 + 2 = 6个空位。先将longest隔一个放一个，
    放成 1 _ 1 _ 1 _ 然后1号盒子中剩余的1个小球无论怎么放都无法避免相邻。所以，必须得有longest <= rest + 1。

    对于充分性，可以通过构造来证明，当longest <= rest + 1时，一定能合法地摆放所有小球。首先摆放longest，
    隔一个放一个，由于longest <= rest + 1，longest一定能不相邻地摆完。然后，对于剩下的小球，从longest摆放的
    最后一个位置往右，以循环数组的方式隔一个摆一个即可。这样就以构造的方式表明当longest <= rest + 1时可以合法摆完。

    具体来说，longest == rest + 1时，例如nums = {3,1,1}，则1号盒子摆完后是这样: 1 _ 1 _ 1，剩下的小球直接摆进去即可，会
    有1号盒子的小球间隔。
    longest == rest时，例如nums = {3,1,2}，则1号盒子摆完后是这样: 1 _ 1 _ 1 _，先在最后的那个位置摆一个小球，然后就相当于上面
    的情况。

    再回到最多能摆多少个小球的问题，
        当longest <= rest + 1时，可以全部摆完，return total
        否则，此时最多可以摆放多少个？首先，此时longest一定无法摆放完，且最多可以摆放rest + 1个(相当于longest' = rest + 1)，
        longest最多可以摆放rest + 1个的前提下，上面的构造方案是可以摆完rest的，因此rest + 1 + rest一定就是最大可摆放数。
    */
    long long numberOfWeeks(const vector<int>& nums) {
        // longest为max(nums), total为sum(nums)
        long long longest = 0;
        long long total = 0;
        for (long long num : nums) {
            longest = max(longest, num);
            total += num;
        }
        long long rest = total - longest;
        if (longest <= rest + 1) return total;
        else return rest + 1 + rest;
    }
};

int main(int argc, char const *argv[]) {
    Solution1953 solu;
    cout << solu.numberOfWeeks({1,2,3}) << endl;
    return 0;
}

/*
url: https://leetcode.cn/problems/minimum-cost-to-equalize-array/
参考: https://leetcode.cn/problems/minimum-cost-to-equalize-array/solutions/2766600/fen-lei-tao-lun-on-zuo-fa-pythonjavacgo-9bsb4/
      https://www.bilibili.com/video/BV1Nf421U7em/
      https://leetcode.cn/problems/minimum-cost-to-equalize-array/solutions/2765974/mei-ju-by-tsreaper-l8id/
相关: LeetCode1953. 你可以工作的最大周数
标签: LeetCode第396场周赛, 贪心, 构造, 数学
*/

// 这次周赛做出前3题。这第4题很难

#include <bits/stdc++.h>

using namespace std;

// 这题需要用到`LeetCode1953. 你可以工作的最大周数`
class Solution3139 {
public:
    /* 参考灵茶山艾府的题解和视频讲解。
    首先，这题不一定最优解是把所有元素全变成nums的最大值，以nums = {1,3,4,4}，cost1=999，cost2=1为例，
    最优方案是这样变：2 4 4 4, 3 5 4 4, 4 5 5 4, 5 5 5 5，这样避免了用操作1，只用操作2就把所有元素全变相等了。

    当n <= 2时，只能用操作1

    当cost1 * 2 <= cost2时，直接全用操作1即可。
    当cost1 * 2 > cost2时，应该尽量使用操作2。
    最多能使用多少次操作2？
    考虑最终所有元素都变成的值x，nums的每个元素都要增长x - nums[i]，这相当于n个盒子，每个盒子有x - nums[i]个
    小球，将这些小球尽量摆放，让来自同一个盒子的小球不相邻，然后每2个相邻的小球为一组，就对应一次操作2。

    以d记max(x - nums[i]) = x - min(nums[i])，s记sum(x - nums[i]) = x * n - sum(nums[i])，
    当d <= s - d + 1时，由`LeetCode1953. 你可以工作的最大周数`的结论，
    可以把总共s个球完成摆放，也就是说只用操作2就可以把所有元素全变为x。这里s可能是奇数，操作2是以2个为单位操作的，
    所以多出来的那个不能用操作2完成，要多用一次操作1。
    总代价 = (s / 2 * cost2) + s % 2 * cost1 = (n / 2 * cost2)x - sum / 2 * cost2 + s % 2 * cost1
    斜率为正
    

    当d > s - d + 1时，和`LeetCode1953. 你可以工作的最大周数`的处理方法一致，从d中分s - d个与s-d配对，然后剩下的用操作1。
    总代价 = (s - d) * cost2 + (d - (s - d)) * cost1
        = [(n - 1)cost2 + (2 - n)cost1]x -(cost2-cost1)sum(nums[i]) - (2cost1-cost2)min(nums[i])
    斜率不确定，可正可负可0

    注意这里随x增大，是先发生d > s - d + 1的情况，再发生d <= s - d + 1的情况

    d = s - d + 1对应x = (sum(nums[i]) - 2min(nums[i]) - 1) / (n - 2)，记x0 = (sum - 2min - 1) / (n - 2) + 1（注意要取向上取整的那个位置），然后尝试x0, x0 - 1, x0 + 1

    x的范围是[max(nums), 正无穷)
    
    于是，只需枚举x在x0和max(nums)附近的点的函数值即可，注意还要满足候选点 >= max(nums)
    */
    int minCostToEqualizeArray(const vector<int>& nums, int cost1, int cost2) {
        const int MOD = 1e9 + 7;
        long long n = nums.size();
        int m = INT_MAX, M = 0; // nums的最小最大
        long long sum = 0; // sum(nums)
        for (int num : nums) {
            m = min(m, num);
            M = max(M, num);
            sum += num;
        }
        if (n <= 2 || cost1 * 2 <= cost2) return (n * M - sum) * cost1 % MOD;
        int x0 = (sum - 2 * m - 1) / (n - 2) + 1;
        vector<long long> candidates;

        // 用lambda获得一个函数对象免得定义一个f函数传参数麻烦
        auto f = [&](int x) -> long long {
            long long d = x - m;
            long long s = n * x - sum;
            if (d <= s - d + 1) return (s / 2 * cost2) + s % 2 * cost1;
            else return (s - d) * cost2 + (d - (s - d)) * cost1;
        };

        candidates.push_back(f(M));
        candidates.push_back(f(M + 1));
        if (x0 >= M) candidates.push_back(f(x0));
        if (x0 - 1 >= M)candidates.push_back(f(x0 - 1));
        if (x0 + 1 >= M)candidates.push_back(f(x0 + 1));
        return *min_element(candidates.begin(), candidates.end()) % MOD;
    }
};

int main(int argc, char const *argv[]) {
    Solution3139 solu;
    // cout << solu.minCostToEqualizeArray({4, 1}, 5, 2) << endl;
    // cout << solu.minCostToEqualizeArray({2,3,3,3,5}, 2, 1) << endl;
    // cout << solu.minCostToEqualizeArray({60,19,53,31,57}, 60, 2) << endl;
    cout << solu.minCostToEqualizeArray({1, 1000000}, 1000000, 1) << endl;
    return 0;
}

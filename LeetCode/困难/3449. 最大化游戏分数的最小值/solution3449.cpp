/*
url: https://leetcode.cn/problems/maximize-the-minimum-game-score/
参考: https://www.bilibili.com/video/BV1ekN2ebEHx/
标签: LeetCode第436场周赛, 二分
*/

// 这次周赛2题

#include <bits/stdc++.h>

using namespace std;

class Solution3449 {
public:
    /* 参考灵茶题解，
    最大化最小值的问题，考虑二分。
    如何check m步内能否让得分都>= mid?
    贪心，首先，行走的路径虽然可能会错综复杂，但是可以重新排列，当gameScore[i]不够mid时，排列后的行走序列先在i
    位置来回走，反复横跳（也会顺便将下一个位置变大），然后变够之后开始看下一个位置。
    这个把行走路径重排成反复横跳的证明技巧很巧妙。

    假设要现在要测试的gameScore最小值为low，某个位置的值为p，每次增加p，从0到>=low，则至少需要增加的次数为 ⌈low / p⌉，
    最开始在-1，points = [1 2 3]，则-1调到1一次(注意是箭头目的地的数增加)，则1到2跳⌈low / p⌉ - 1次，2到1跳⌈low / p⌉ - 1次，共 2 * ⌈low / p⌉ - 1 次操作即可完成对1的增加，
    同时，2也已经增加了⌈low / p⌉ - 1次。
    */
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();

        auto check = [&](long long low) {
            int pre = 0;
            int rem = m; // 剩余可用步数
            for (int i = 0; i < n; i++) {
                int p = points[i];
                int k = (low + p - 1) / p; // 需要增加的次数⌈low / p⌉
                k -= pre; // 前面顺便进行了增加，现在的k才是p真正需要的增加次数
                if (i == n - 1 && k <= 0) return true; // 最后一个数借助n - 2来反复横跳
                rem -= max(2 * k - 1, 1); // 这里要和1取max是因为即使已经够大，也需要操作一次往右走，但是如果已经到了n - 1位置就不用了
                if (rem < 0) return false;
                pre = max(k - 1, 0); // i 没有借助 i + 1 反复横跳来增加gameScore[i]，对 i + 1 的增加次数就是0
            }
            return true;
        };

        // 搜索最后一个'是'
        long long left = 1; // 注意check当mid=0时实际应当返回true，但是以上check代码会返回false，因为会认为需要向右走增大右边的数，而实际不需要。这里left初值要为1
        long long min = *min_element(points.begin(), points.end());
        // 把所有都用来增加points最小值，不论其位置，最多也只能增加 1 + (m - 1) / 2 次
        long long right = (m + 1) / 2 * min; // right的回答为是或否，但是right + 1一定是否
        while (left <= right) {
            long long mid = (left + right) / 2;
            if (check(mid)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return right;
    }
};

int main(int argc, char const *argv[]) {
    Solution3449 solu;
    // cout << solu.maxScore(*new vector<int>{1,2,3}, 5) << endl;
    // cout << solu.maxScore(*new vector<int>{4,5}, 1) << endl;
    cout << solu.maxScore(*new vector<int>{7,8,6}, 1) << endl;
    return 0;
}
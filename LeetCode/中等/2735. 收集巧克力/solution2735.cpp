// https://leetcode.cn/problems/collecting-chocolates/description/

#include <bits/stdc++.h>

using namespace std;

class Solution2735 {
public:
    long long minCost(const vector<int>& nums, int x) {
        /* 题目能做的操作方向是定的，(i + 1) mod n，不用考虑可能顺时针也可能逆时针操作。
        最多操作n次，每个位置的点都能见到最小值，所以操作次数最多n次。
        */
        int n = nums.size();
        // 枚举操作次数
        vector<int> mins(n); // 每个位置操作i次下见到的最小值
        for (int i = 0; i < n; i++) mins[i] = nums[i];
        long long ans = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            long long sum = 0;
            for (int j = 0; j < n; j++) {
                // 最新的一次操作对某个j新引见的值是nums[(j + i) % n]
                mins[j] = min(mins[j], nums[(j + i) % n]);
                sum += mins[j];
            }
            ans = min(ans, sum + (long long)i * x);
        }
        return ans;
    }

    /* 待做: [官方题解](https://leetcode.cn/problems/collecting-chocolates/solutions/2580148/shou-ji-qiao-ke-li-by-leetcode-solution-bjyp/)
    给了个二次差分的解法，时间复杂度能O(n)，但是官解说了这个方法难度较大，感觉会很难理解，后面再看。 */
};

int main(int argc, char const *argv[]) {
    Solution2735 solu;
    cout << solu.minCost({20,1,15}, 5) << endl;
    return 0;
}

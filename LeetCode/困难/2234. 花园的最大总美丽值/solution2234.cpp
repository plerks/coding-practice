/*
url: https://leetcode.cn/problems/maximum-total-beauty-of-the-gardens/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2234 {
public:
    /* 我的想法，错误，从{20,1,15,17,10,2,4,16,15,11}, 2, 20, 10, 2这个用例能看出来，
    要把非完善的花园的最小值尽量变大，不能简单除，因为不能动已经种了的花
    */
    long long maximumBeauty_wa(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n = flowers.size();
        long long ans = 0;
        sort(flowers.begin(), flowers.end());
        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + flowers[i];
        }
        // 枚举完善花园的数量
        int r = n; // 初始的完善花园数量
        while (r - 1 >= 0 && flowers[r - 1] >= target) r--;
        // 初始[0, r)是不完善，[r, n - 1]是完善花园
        // newFlowers能把不完善花园的最小值变多大？x * r <= sum([0, r)) + newFlowers，搜索最后一个x。但是x是整数，可以直接除，不用二分
        long long t = 1LL * (n - r) * full;
        if (r > 0) {
            int x = (pre[r] + newFlowers) / r;
            if (x >= target) x = target - 1;
            t += x * partial;
        }
        ans = max(ans, t);
        r--;
        while (r >= 0) {
            newFlowers -= target - flowers[r]; // 尝试把r变成完善花园，现在[0, r)不完善，[r, n - 1]完善
            if (newFlowers < 0) break; // 不能弄出这么多完善花园
            // 把r变完善，[r, n - 1]都是完善花园
            long long t = 1LL * (n - r) * full;
            if (r > 0) {
                int x = (pre[r] + newFlowers) / r;
                if (x >= target) x = target - 1;
                t += x * partial;
            }   
            ans = max(ans, t);
            r--;
        }
        return ans;
    }

    /* 参考官方题解，上面算非完善花园能达到的最小值的错误在于，找出的x值，可能有部分花园的值大于x，这样算出的值
    就潜在地把多的花移动过去了。例如1 3 5，用x * r <= sum([0, r)) + newFlowers的思路算，把所有都变成>=3要
    补充多少花？3 * 3 - (1 + 3 + 5) = 0！但是实际是要补充的，因为不能把5移动过去。但是1 3 5，把所有都变成>=5
    要补充多少花？5 * 3 - (1 + 3 + 5) = 6，是正确的！这是因为这时要变成的值是最大值。
    */
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n = flowers.size();
        long long ans = 0;
        sort(flowers.begin(), flowers.end());
        int r = n;
        while (r - 1 >= 0 && flowers[r - 1] >= target) r--; // [r, n - 1]初始为完善花园
        int j = r - 1;
        long long pre = accumulate(flowers.begin(), flowers.begin() + r, 0LL);
        for (; r >= 0; r--) {
            if (r != n) newFlowers -= max(0, target - flowers[r]); // r变完善花园，看[0, r)的最小值能变多大，newFlowers为剩余花数
            if (newFlowers < 0) break; // 剩余花不够变完善花园
            /* 非完善花园能达到的最大min，一个上限一个上限试，例如，1 3 5 6，先试剩下的花
            newFlowers能不能铺平成6，能的话再把剩下的再平均，不行的话再试newFlowers能不能铺平成5，假设能
            由于不能铺平成6，则最终值一定在[5, 6)，再把剩余的平均给1 3 5
            */
            while (j >= 0 && (j >= r || 1LL * flowers[j] * (j + 1) - pre > newFlowers)) { // r > 0时，j一定在0处可铺平
                pre -= flowers[j];
                j--;
            }
            int x;
            if (j == -1) x = 0; // [0, n - 1]为完善花园，没有非完善花园
            else x = min(flowers[j] + (newFlowers - (1LL * flowers[j] * (j + 1) - pre)) / (j + 1), (long long)target - 1);
            ans = max(ans, 1LL * (n - r) * full + 1LL * x * partial);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2234 solu;
    // cout << solu.maximumBeauty(*new vector<int>{1,3,1,1}, 7, 6, 12, 1) << endl;
    // cout << solu.maximumBeauty(*new vector<int>{8,2}, 24, 18, 6, 3) << endl;
    cout << solu.maximumBeauty(*new vector<int>{2,4,5,3}, 10, 5, 2, 6) << endl;
    // cout << solu.maximumBeauty(*new vector<int>{20,1,15,17,10,2,4,16,15,11}, 2, 20, 10, 2) << endl;
    return 0;
}
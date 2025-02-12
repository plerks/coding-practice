/*
url: https://leetcode.cn/problems/apply-operations-to-maximize-frequency-score/
参考: https://leetcode.cn/problems/apply-operations-to-maximize-frequency-score/solutions/2569301/hua-dong-chuang-kou-zhong-wei-shu-tan-xi-nuvr/
标签: 【题单】滑动窗口与双指针, 中位数贪心, 贡献法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2968 {
public:
    /* 我的解法，二分，滑窗有些题就这样，次优做法是二分，时间复杂度从用滑窗的O(n)到用二分的O(nlogn)，
    不过这题要排序，所以用滑窗用二分时间复杂度都是O(nlogn)
    */
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size();
        // 不关心值与原位置的对应关系，可排序
        sort(nums.begin(), nums.end());
        int left = 1, right = n;
        // 假设把[l, r]全变为x，则x应该选中位数。二分能在k步内转换为全等的长度

        auto check = [&](int len) {
            long long mid = len / 2;
            long long pre = 0, suf = 0; // 这里分解为前后缀计算操作次数
            for (int i = 0; i < mid; i++) pre += nums[i];
            for (int i = mid + 1; i < len; i++) suf += nums[i];
            if (nums[mid] * mid - pre + suf - (len - 1 - mid) * nums[mid] <= k) return true;
            for (int i = 1; i <= n - len; i++) {
                pre -= nums[i - 1];
                pre += nums[mid];
                suf -= nums[mid + 1];
                suf += nums[i + len - 1]; 
                mid++;
                if (nums[mid] * (long long)(len / 2) - pre + suf - (long long)(len - 1 - len / 2) * nums[mid] <= k) return true;
            }
            return false;
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }

    /* 灵茶题解做法，虽然滑窗过程中子数组中位数会变，但是若[l, r]不能k步全等，[l-1, r]则一定也不能k步全等，
    所以是具备单调性的。
    */
    int maxFrequencyScore_implementation2(vector<int>& nums, long long k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        /* 以[a0, a1, a2, a3]为例，操作次数为 (a2-a1) + (a3-a1) + (a1 - a0) = (a2 + a3) - (a0 + a1)
        以[a0, a1, a2, a3, a4]为例，操作次数为 (a3 + a4) - (a0 + a1)，
        用贡献法的思路来看，右边的a[i]贡献一个a[i] - a[mid]，左边贡献一个a[mid] - a[i]，a[mid]被约掉，最后结果为右半之和 - 左半之和。
        根本与中位数无关！
        于是可以视为右半贡献nums[i]，左半贡献-nums[i]，中间那刀位置的贡献为0，但是不一定那位置有数
        这个贡献法的思路相比计算前后缀和，非常巧妙！
        */
        int l = 0;
        long long s = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            // r进入，相对正中分割线位置会变动的是上中位数(l + r) / 2，贡献从nums[(l + r) / 2]到0，或者0到-nums[(l + r) / 2]，增量都是-nums[(l + r) / 2]
            s += nums[r] - nums[(l + r) / 2];
            while (s > k) {
                s += nums[l] - nums[(l + r + 1) / 2]; // 同样地分析贡献，相对正中分割线位置会变动的仍是上中位数，不过这次(l + r + 1) / 2才是上中位数
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2968 solu;
    cout << solu.maxFrequencyScore(*new vector<int>{1,2,6,4}, 3) << endl;
    cout << solu.maxFrequencyScore(*new vector<int>{1,4,4,2,4}, 0) << endl;
    cout << solu.maxFrequencyScore(*new vector<int>{10}, 0) << endl;

    cout << solu.maxFrequencyScore_implementation2(*new vector<int>{1,2,6,4}, 3) << endl;
    return 0;
}
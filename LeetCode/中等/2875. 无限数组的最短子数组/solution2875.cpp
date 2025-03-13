/*
url: https://leetcode.cn/problems/minimum-size-subarray-in-infinite-array/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2875 {
public:
    int minSizeSubarray(vector<int>& nums, long long target) {
        int n = nums.size();
        long long total = accumulate(nums.begin(), nums.end(), 0LL);

        long long cnt = target / total;
        long long baseLen = cnt * n;
        target = target % total;

        int ans = n + 1;
        long long sum = 0;
        for (int l = 0, r = 0; r < n; r++) {
            sum += nums[r];
            while (l <= r && sum >= target) {
                sum -= nums[l];
                l++;
            }
            // 现在l的位置<target
            if (l > 0 && sum + nums[l - 1] == target) ans = min(ans, r - l + 2);
        }
        // 这里nums相当于循环数组，要处理另外一种取法
        sum = 0;
        target = total - target; // 这个解法这里可能超int，target得是long long
        for (int l = 0, r = 0; r < n; r++) {
            sum += nums[r];
            while (l <= r && sum >= target) {
                sum -= nums[l];
                l++;
            }
            if (l > 0 && sum + nums[l - 1] == target) ans = min(ans, n - (r - l + 2));
        }

        return ans == n + 1 ? -1 : baseLen + ans;
    }

    // 参考灵茶题解写法，简洁很多，最后一段相当于把nums拼一次到尾部然后滑窗，但是不需要真的拼接，只需要mod就行
    int minSizeSubarray_implementation2(vector<int>& nums, int target) {
        int n = nums.size();
        long long total = accumulate(nums.begin(), nums.end(), 0LL);

        long long cnt = target / total;
        long long baseLen = cnt * n;
        target = target % total;

        int ans = n + 1;
        long long sum = 0;
        for (int l = 0, r = 0; r < 2 * n; r++) {
            sum += nums[r % n];
            // 这题target >= 1，当l==r时，循环结束sum变为0，下一次l == r + 1(窗口为空)时，一定不会进循环，所以不需要用while(l <= r)防下标越界
            while (sum > target) { // nums[i] >= 1，所以不存在连续位置==target，要往右缩的情况
                sum -= nums[l % n];
                l++;
            }
            if (sum == target) ans = min(ans, r - l + 1);
        }
        return ans == n + 1 ? -1 : baseLen + ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2875 solu;
    cout << solu.minSizeSubarray(*new vector<int>{1,1,1,2,3}, 4) << endl;
    cout << solu.minSizeSubarray(*new vector<int>{2,3,5,2,3,4,4,1,3,5,2,2,5,1,1,2,5}, 19) << endl;

    cout << solu.minSizeSubarray_implementation2(*new vector<int>{1,1,1,2,3}, 4) << endl;
    cout << solu.minSizeSubarray_implementation2(*new vector<int>{2,3,5,2,3,4,4,1,3,5,2,2,5,1,1,2,5}, 19) << endl;
    return 0;
}
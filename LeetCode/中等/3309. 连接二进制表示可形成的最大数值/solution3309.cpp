/*
url: https://leetcode.cn/problems/maximum-possible-number-by-binary-concatenation/
参考: https://leetcode.cn/problems/maximum-possible-number-by-binary-concatenation/solutions/2940489/fei-bao-li-zuo-fa-onlogn-pai-xu-pythonja-540j/
标签: LeetCode第418场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3309 {
public:
    int maxGoodNumber(vector<int>& nums) {
        int a = nums[0];
        int b = nums[1];
        int c = nums[2];
        int len1 = 32 - __builtin_clz(nums[0]);
        int len2 = 32 - __builtin_clz(nums[1]);
        int len3 = 32 - __builtin_clz(nums[2]);
        return max({
            (a << (len2 + len3)) + (b << len3) + c,
            (a << (len2 + len3)) + (c << len2) + b,
            (b << (len1 + len3)) + (a << len3) + c,
            (b << (len1 + len3)) + (c << len1) + a,
            (c << (len1 + len2)) + (a << len2) + b,
            (c << (len1 + len2)) + (b << len1) + a
        });
    }

    // 灵茶山艾府题解做法，这样即便nums的元素很多也能做，只是最后改下，要把ans换成string拼接
    int maxGoodNumber_implementation2(vector<int>& nums) {
        // 注意这里不能简单地让字典序大的在前，例如[8, 82]，则882最大，[8, 89]，则898最大
        sort(nums.begin(), nums.end(), [&](int a, int b) {
            int len1 = 32 - __builtin_clz(a);
            int len2 = 32 - __builtin_clz(b);
            // 比较ab和ba哪个大
            return (a << len2 | b) > (b << len1 | a);
        });

        int ans = 0;

        for (int i = 0; i < nums.size(); i++) {
            ans = ans << (32 - __builtin_clz(nums[i])) | nums[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3309 solu;
    vector<int> nums = {2, 8, 16};
    cout << solu.maxGoodNumber(nums) << endl;
    cout << solu.maxGoodNumber_implementation2(nums) << endl;
    return 0;
}

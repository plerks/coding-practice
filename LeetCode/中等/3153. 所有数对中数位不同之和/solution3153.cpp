/*
url: https://leetcode.cn/problems/sum-of-digit-differences-of-all-pairs/description/
LeetCode参考: https://leetcode.cn/problems/sum-of-digit-differences-of-all-pairs/solutions/2782811/chai-wei-suan-gong-xian-yi-ci-bian-li-by-46rf/
标签: LeetCode第398场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3153 {
public:
    /* 周赛时的解法，通过。
    按数字位进行划分，求出某位上0-9的出现次数，在某一位上的不同数位对为某个数字的出现次数 * (total - 这个数字的出现次数)，不过这样重复
    算了，最后要除2。 */
    long long sumDigitDifferences(vector<int>& nums) {
        int n = nums.size();
        int digitLen = to_string(nums[0]).size();
        vector<vector<long long>> vec(digitLen, vector<long long>(10, 0));
        for (int num : nums) {
            string s = to_string(num);
            for (int i = 0; i < digitLen; i++) {
                vec[i][s[i] - '0']++;
            }
        }
        long long ans = 0;
        for (int i = 0; i < digitLen; i++) {
            auto &map = vec[i];
            long long total = 0;
            for (int i = 0; i < 10; i++) total += map[i];
            for (int i = 0; i < 10; i++) {
                ans += map[i] * (total - map[i]);
            }
        }
        return ans / 2;
    }

    // 灵茶山艾府题解解法，在遍历过程中统计不同的数位对数
    long long sumDigitDifferences_implementation2(vector<int>& nums) {
        int n = nums.size();
        int digitLen = to_string(nums[0]).size();
        long long ans = 0;
        vector<array<int, 10>> count(digitLen);
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = 0; x > 0; x /= 10, j++) {
                int d = x % 10;
                ans += i - count[j][d]; // i为当前在j位置已处理的数的总数，i - count[j][d]为前面的数在这一位置上不同于d的次数
                count[j][d]++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

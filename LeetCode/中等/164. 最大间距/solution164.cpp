/*
url: https://leetcode.cn/problems/maximum-gap/
相关: LeetCode220. 存在重复元素 III
*/

#include <bits/stdc++.h>

using namespace std;

class Solution164 {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        int m = INT_MAX;
        int M = INT_MIN;
        for (int x : nums) {
            m = std::min(m, x);
            M = std::max(M, x);
        }

        /* 每个桶长度为 ⌊(M - m) / (n - 1)⌋ ，每个桶左闭右开，最大间距一定比这个平均分布的情况大或相等，所以不用考虑桶内部。
        但是都左闭右开，M会包含不到，所以用桶来装 [m, M + 1) 的范围，需要的桶的个数为 k d >= M + 1 - m，
        k 取 ⌈(M + 1 - m) / d⌉ = (M + 1 - m + d - 1) / d = (M - m + d) / d
        */
        int d = (M - m) / (n - 1); // 桶长度
        d = max(1, d); // 防止除0，如果MaxGap果真为0 (nums元素全相同)，最后的结果也会是0
        int cnt = (M - m + d) / d; // 需要的桶个数，大约为 n ，即使 0 <= nums[i] <= 1e9，nums[i] 范围为1e9级别也没事

        vector<pair<int, int>> buckets(cnt, {INT_MAX, INT_MIN}); // 每个桶记录自己内的 {min, max}
        for (int x : nums) {
            int index = (x - m) / d;
            buckets[index].first = std::min(buckets[index].first, x);
            buckets[index].second = std::max(buckets[index].second, x);
        }

        // 最大间距一定不在同一个桶内。必在桶之间，不过可能跨越多个桶，因为有些桶可能没元素。
        int ans = 0;
        int pre = -1; // 上一个有效值
        for (int i = 0; i < buckets.size(); i++) { // 枚举最大间距的右端点，一定为某个first
            if (buckets[i].first != INT_MAX) { // 有first一定也有second，这里相当于判断桶是否为空
                if (pre != -1) ans = std::max(ans, buckets[i].first - pre);
                pre = buckets[i].second;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution164 solu;
    // cout << solu.maximumGap(*new vector<int>{3,6}) << endl;
    // cout << solu.maximumGap(*new vector<int>{3,6,9,1}) << endl;
    // cout << solu.maximumGap(*new vector<int>{1,3,100}) << endl;
    cout << solu.maximumGap(*new vector<int>{0,0,0}) << endl;
    cout << solu.maximumGap(*new vector<int>{1,1,1,1,1,5,5,5,5,5}) << endl;
    return 0;
}
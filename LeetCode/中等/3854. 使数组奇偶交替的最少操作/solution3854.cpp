/*
url: https://leetcode.cn/problems/minimum-operations-to-make-array-parity-alternating/
标签: LeetCode第177场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3854 {
public:
    /*
    双周赛时写了很长的乱七八糟的dp，调来调去最后还是会wa，思路有问题。
    参考灵茶题解：把数往中间调
    */
    vector<int> makeParityAlternating(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return {0, 0};
        int mi = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        auto calc = [&](int start) -> vector<int> { // start 为开头的奇偶性
            int op = 0;
            int t_mi = INT_MAX, t_mx = INT_MIN;
            for (int i = 0; i < n; i++) {
                int x = nums[i];
                // 注意 x 可能是负数，x % 2 不是预期的结果，但 x & 1 是
                // 需要修改当前位置的奇偶性，往中间改，极差最小，只有最大最小值的 x 会影响极差的值
                if ((x & 1) != (start ^ (i % 2))) {
                    op++;
                    if (x == mi) x++;
                    else if (x == mx) x--;
                }
                t_mi = min(t_mi, x);
                t_mx = max(t_mx, x);
            }
            // 对于 0 1 2 ，start == 1，该变成 1 (0/2) 1 ，这时候 t_mx - t_mi 会是 0，要和 1 取 max 结果才是对的
            // 但这又要特殊考虑只有一个数的情况，否则会认为只有一个数也要操作一次
            return {op, max(t_mx - t_mi, 1)};
        };

        return min(calc(0), calc(1));
    }

    // 灵茶题解的另外一种解法，出发点更简单，但是常数大
    // 枚举开头是奇/偶，那么就知道了每个位置该不该改，如果 x 要改，那么就是 {x - 1, x + 1} 选一个数，否则就是 {x}
    // 结果变成了从 n 个列表中选一个最小 [l, r] 使得每个列表都包含至少一个数，这是 LeetCode632
    vector<int> makeParityAlternating_impl2(vector<int>& nums) {
        int n = nums.size();

        auto calc = [&](int start) -> vector<int> {
            vector<vector<int>> t;
            int op = 0;
            for (int i = 0; i < n; i++) {
                int x = nums[i];
                if ((x & 1) != (start ^ (i % 2))) {
                    op++;
                    t.push_back(vector<int>{x - 1, x + 1});
                }
                else t.push_back(vector<int>{x});
            }
            auto v = smallestRange(t);
            return {op, v[1] - v[0]};
        };

        return min(calc(0), calc(1));
    }

    // LeetCode632
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size(); // k个序列
        vector<pair<int, int>> pos; // (位置, 所属序列)
        for (int i = 0; i < k; i++) {
            for (auto p : nums[i]) {
                pos.push_back({p, i});
            }
        }
        sort(pos.begin(), pos.end());
        int ans_l = -1e9;
        int ans_r = 1e9;
        vector<int> cnt(k); // 窗口中各序列数字的出现次数
        int full = 0; // 窗口中还缺存在多少个序列中的数字
        int l = 0;
        for (int r = 0; r < pos.size(); r++) {
            auto [pr, seqr] = pos[r]; // (位置, 所属序列)
            cnt[seqr]++;
            if (cnt[seqr] == 1) full++;
            while (full >= k) {
                auto [pl, seql] = pos[l];
                cnt[seql]--;
                if (cnt[seql] == 0) full--;
                l++;
            }
            if (l != 0) {
                // [l - 1, r]这个窗口合法
                if (pr - pos[l - 1].first < ans_r - ans_l) {
                    ans_l = pos[l - 1].first;
                    ans_r = pr;
                }
            }
        }
        return {ans_l, ans_r};
    }
};

int main(int argc, char const *argv[]) {
    Solution3854 solu;
    auto a = solu.makeParityAlternating(*new vector<int>{7});
    return 0;
}
/*
url: https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/
相关: LeetCode2953. 统计完全子字符串
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution632 {
public:
    // 我的解法，超时，时间复杂度O(k * n * k)，n为最大nums[i]长度，k * n代表nums所有点的总数的上界
    vector<int> smallestRange_tle(vector<vector<int>>& nums) {
        int k = nums.size(); // k个序列
        vector<int> pos;
        for (auto vec : nums) {
            for (auto p : vec) {
                pos.push_back(p);
            }
        }
        sort(pos.begin(), pos.end());
        vector<int> idx(k);
        vector<int> ans = {0, INT_MAX};
        for (int r : pos) { // 枚举右边界
            int l = r;
            bool ok = true;
            for (int i = 0; i < k; i++) { // 看这个r是否能找到l，使得k个序列都能含至少一个数
                auto &seq = nums[i];
                while (idx[i] < seq.size() && seq[idx[i]] <= r) {
                    idx[i]++;
                }
                if (idx[i] - 1 == -1) {
                    ok = false;
                    break;
                }
                l = min(l, nums[i][idx[i] - 1]); // 对于第i个序列，在idx[i]位置就可以，但是所有的序列都要含有数，所以要取最左
            }
            if (ok) {
                if (r - l < ans[1] - ans[0]) {
                    ans = {l, r};
                }
            }
        }
        return ans;
    }

    /* 灵茶题解解法一，堆
    上面tle的原因是多了一层k指针的循环，那层循环的目的在于让每个指针向右移动到够大的位置，那么
    换一种思路，枚举左端点位置，对于k个有序序列，用堆即可拿出最小值，而对这个左端点，序列的头都会
    比它大，于是只需要求序列头中最大的就可以知道以l开头的左端点，r要大到多少才能让k个序列都包含一个数了。
    对于求序列头最大的值，由于每个序列头都是在变大的，所以只需用一个变量就可以求出最大值了。
    
    时间复杂度O(knlogk)，n为最大nums[i]长度，k * n代表nums所有点的总数的上界
    */
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size(); // k个序列

        vector<int> idx(k, 0); // k指针

        auto comp = [&](int x, int y) {
            return nums[x][idx[x]] > nums[y][idx[y]];
        };

        priority_queue<int, vector<int>, decltype(comp)> pq(comp);
        int mx = INT_MIN;
        // 1 <= nums[i].length <= 50，都有元素，当任意一个nums[i]元素拿完后，后面一定无法满足
        for (int i = 0; i < k; i++) {
            pq.push(i);
            mx = max(mx, nums[i].front());
        }

        int ans_l = -1000000;
        int ans_r = 1000000;
        
        while (true) {
            int lp = pq.top(); pq.pop(); // lp表示最小的是哪个序列头
            int l = nums[lp][idx[lp]];
            if (mx - l < ans_r - ans_l) {
                ans_l = l;
                ans_r = mx;
            }
            idx[lp]++;
            if (idx[lp] == nums[lp].size()) break;
            pq.push(lp);
            mx = max(mx, nums[lp][idx[lp]]);
        }
        return {ans_l, ans_r};
    }

    /* 灵茶题解解法二，滑动窗口，
    把所有点排好序之后，用一个滑动窗口来做，窗口要满足的条件是，包含属于k个序列的点
    */
    vector<int> smallestRange_implementation2(vector<vector<int>>& nums) {
        int k = nums.size(); // k个序列
        vector<pair<int, int>> pos; // (位置, 所属序列)
        for (int i = 0; i < k; i++) {
            for (auto p : nums[i]) {
                pos.push_back({p, i});
            }
        }
        sort(pos.begin(), pos.end());
        int ans_l = -1000000;
        int ans_r = 1000000;
        vector<int> cnt(k); // 窗口中各序列数字的出现次数
        int full = 0; // 窗口中还缺存在多少个序列中的数字
        // 这里为了知道有多少种成分，而去记各种成分的频率，并在0-1的边界点更新full的技巧，和LeetCode2953. 统计完全子字符串类似
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
    Solution632 solu;
    auto a = solu.smallestRange(*new vector<vector<int>>{{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}});
    auto b = solu.smallestRange_implementation2(*new vector<vector<int>>{{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}});
    return 0;
}
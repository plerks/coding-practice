/*
url: https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/description/
参考: https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/2254860/hua-dong-chuang-kou-jian-ji-xie-fa-pytho-1c2d/
标签: 【题单】滑动窗口与双指针, 同向双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2106 {
public:
    // 我的解法，枚举第一步的方向和步数，然后就能算出能遍历到的区间，然后用前缀和求水果数
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        int mx = 2e5;
        vector<int> nums(mx + 1);
        for (int i = 0; i < n; i++) nums[fruits[i][0]] = fruits[i][1];
        vector<long long> pre(mx + 2);
        for (int i = 0; i <= mx; i++) {
            pre[i + 1] = pre[i] + nums[i];
        }
        int ans = INT_MIN;
        // 第一步往右走，枚举右边界的位置，并计算左边界位置，然后用前缀和计算区间水果数
        for (int r = k; r >= 0; r--) { // r为向右走的步数
            // 折返回来后左边界为 startPos - (k - 2r)
            int hi = startPos + r;
            hi = min(hi, mx);
            int lo = max(0, startPos - (k - 2 * r));
            lo = min(startPos, lo);
            ans = max(ans, (int)(pre[hi + 1] - pre[lo - 1 + 1]));
        }
        // 第一步往左走
        for (int l = k; l >= 0; l--) {
            int lo = startPos - l;
            lo = max(0, lo);
            int hi = startPos + (k - 2 * l);
            hi = min(hi, mx);
            hi = max(startPos, hi);
            ans = max(ans, (int)(pre[hi + 1] - pre[lo - 1 + 1]));
        }
        return ans;
    }

    /* 灵茶题解解法，用同向的双指针滑窗，
    先找到最靠左的>=startPos - k的position，这是能向左摘到最远水果，然后，
    [left, startPos]的水果都能摘到，然后枚举右端点，何时需要向右移动左端点？
    当不管初始先向左还是先向右都到达不了当前的left时，left++
    */
    int maxTotalFruits_implementation2(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        // 第一个>=start - k的有水果position
        int left = lower_bound(fruits.begin(), fruits.end(), startPos - k, [](auto &x, int y) {
            return x[0] < y;
        }) - fruits.begin();
        int right = left;
        int sum = 0;
        while (right < n && fruits[right][0] <= startPos) {
            sum += fruits[right][1];
            right++;
        }
        int ans = sum;
        for (; right < n && fruits[right][0] <= startPos + k; right++) {
            sum += fruits[right][1];
            // 先往右到right，左最多到达startPos - (k - 2 * (fruits[right][0] - startPos))
            // 先往左到left，右最多到达startPos + (k - 2 * (startPos - fruits[left][0]))
            while (startPos - (k - 2 * (fruits[right][0] - startPos)) > fruits[left][0] &&
                   startPos + (k - 2 * (startPos - fruits[left][0])) < fruits[right][0]) {
                sum -= fruits[left][1];
                left++;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2106 solu;
    cout << solu.maxTotalFruits(*new vector<vector<int>>{{2,8},{6,3},{8,6}}, 5, 4) << endl;
    cout << solu.maxTotalFruits(*new vector<vector<int>>{{200000,10000}}, 0, 200000) << endl;

    cout << solu.maxTotalFruits_implementation2(*new vector<vector<int>>{{2,8},{6,3},{8,6}}, 5, 4) << endl;
    cout << solu.maxTotalFruits_implementation2(*new vector<vector<int>>{{200000,10000}}, 0, 200000) << endl;
    return 0;
}
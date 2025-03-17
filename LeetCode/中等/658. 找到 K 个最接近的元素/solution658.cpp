/*
url: https://leetcode.cn/problems/find-k-closest-elements/
相关: LeetCode1471. 数组中的 k 个最强值
标签: 【题单】滑动窗口与双指针, [mark]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution658 {
public:
    // 我的解法，时间复杂度O(logn + k + logk)
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        // 找最后一个<=x的数
        int index = upper_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;
        int l = index, r = index + 1;
        vector<int> ans(k);
        for (int i = 0; i < k; i++) {
            // 选l的情况: l合法 && (右不合法 || 左比右好)。
            /* [mark]，这样写简洁，比：
            while (l >= 0 && r < n) { ... }
            while (l >= 0) { ... }
            while (r < n) { ... }
            的写法简洁。
            */
            if (l >= 0 && (r == n || abs(arr[l] - x) <= abs(arr[r] - x))) {
                ans[i] = arr[l];
                l--;
            }
            else {
                ans[i] = arr[r];
                r++;
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

    // 官方题解解法，最后的答案一定是arr中的一段区间，直接从arr中取结果，不用排序，时间复杂度O(logn + k)
    vector<int> findClosestElements_implementation2(vector<int>& arr, int k, int x) {
        int n = arr.size();
        // 找最后一个<=x的数
        int index = upper_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;
        int l = index, r = index + 1;
        for (int i = 0; i < k; i++) {
            // 选l的情况: l合法 && (右不合法 || 左比右好)
            if (l >= 0 && (r == n || abs(arr[l] - x) <= abs(arr[r] - x))) {
                l--;
            }
            else {
                r++;
            }
        }
        // l, r都是待尝试的位置，正确区间为[l + 1, r - 1]
        return vector<int>(arr.begin() + l + 1, arr.begin() + r);
    }
};

int main(int argc, char const *argv[]) {
    Solution658 solu;
    // auto a = solu.findClosestElements(*new vector<int>{1,2,3,4,5}, 4, 3);
    // auto b = solu.findClosestElements(*new vector<int>{1}, 1, 1);
    auto c = solu.findClosestElements(*new vector<int>{0,1,1,1,2,3,6,7,8,9}, 9, 4);
    return 0;
}
/*
url: https://leetcode.cn/problems/number-of-subarrays-with-bounded-maximum/
相关: LeetCode2334. 元素值大于变化阈值的子数组, LeetCode2444. 统计定界子数组的数目
标签: 【题单】滑动窗口与双指针, 单调栈, 并查集, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution795 {
public:
    // 我的解法，用单调栈
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size();
        int ans = 0;
        vector<int> posL(n); // 左边第一个>=nums[i]的元素位置
        vector<int> posR(n); // 右边第一个>nums[i]的元素位置
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                posR[st.top()] = i;
                st.pop();
            }
            posL[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        while (!st.empty()) {
            posR[st.top()] = n;
            st.pop();
        }
        for (int i = 0; i < n; i++) { // 枚举nums[i]作为最大值，为了避免相同元素时出现重复，左边不可以选同样的元素，右边可以
            if (nums[i] < left || nums[i] > right) continue;
            int l = posL[i];
            int r = posR[i];
            // (l, i) + i + (i, r - 1]，例如(i, r - 1]长度为r - 1 - i，右侧可以取长度0, 1, ... , r - i
            ans += (i - l) * (r - i);
        }
        return ans;
    }

    /* 参考灵茶题解和官方题解，枚举右端点位置，看左端点能取哪些值。首先，不能含>right，左端点必须大于最近一个>right的位置，
    其次，至少含一个[left, right]，左端点不能靠右到越过最近一个[left, right]的位置
    */
    int numSubarrayBoundedMax_implementation2(vector<int>& nums, int left, int right) {
        int n = nums.size();
        int ans = 0;
        int i0 = -1, i1 = -1;
        for (int i = 0; i < n; i++) {
            /* if (nums[i] > right) i0 = i;
            if (nums[i] >= left && nums[i] <= right) i1 = i;
            ans += max(0, i1 - i0); */
            // 这样写不用处理 i1 - i0 可能为负的情况
            if (nums[i] > right) i0 = i;
            if (nums[i] >= left) i1 = i;
            ans += i1 - i0;
        }
        return ans;
    }

    /* 官方题解的另一种写法，用 所有元素<=right的子数组个数  -  所有元素 <= left - 1的子数组个数，
    即至少包含一个[left, right] = 所有元素<=right - 所有元素<left
    */
    int numSubarrayBoundedMax_implementation3(vector<int>& nums, int left, int right) {
        return count(nums, right) - count(nums, left - 1);
    }

    int count(vector<int> &nums, int bound) {
        int cur = 0;
        int ans = 0;
        for (int x : nums) {
            if (x <= bound) cur++; // cur表示从x能往左延展的，元素都<=bound的长度，应该也可以用分组循环写
            else cur = 0;
            ans += cur;
        }
        return ans;
    }

    // 用`LeetCode2334. 元素值大于变化阈值的子数组`的那种特殊并查集用法来做，时间复杂度O(nlogn)，因为要排序
    int numSubarrayBoundedMax_implementation4(vector<int>& nums, int left, int right) {
        int n = nums.size();
        int ans = 0;
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        vector<int> size(n, 1);
        /* 这里必须用stable_sort，为了计数子数组时不重复，遇到连续的相同元素时必须一边闭一边开，
        但是例如2 2 2，如果后面遍历idx时是先遍历的最后一个2，就会认为向左不能扩展，从而导致漏算子数组
        */
        stable_sort(idx.begin(), idx.end(), [&](const int x, const int y) {
            return nums[x] < nums[y]; // 从小到大排序
        });

        auto find = [&](auto &find, int x) -> int {
            if (parent[x] != x) {
                parent[x] = find(find, parent[x]);
            }
            return parent[x];
        };

        auto unite = [&](int x, int y) {
            int rx = find(find, x), ry = find(find, y);
            if (rx == ry) return;
            parent[ry] = rx;
            size[rx] += size[ry];
        };

        /* 从小到大遍历，枚举nums[i]作为最大值，左右能扩展多远，利用并查集，这个左右扩展不需要O(n)。
        且为了避免重复元素重复计数，一边闭一边开
        */
        for (int i : idx) {
            if (nums[i] > right) break;
            int size_l = 0, size_r = 0;
            if (i - 1 >= 0 && nums[i - 1] <= nums[i]) {
                size_l = size[find(find, i - 1)];
                unite(i - 1, i);
            }
            if (i + 1 < n && nums[i + 1] < nums[i]) {
                size_r = size[find(find, i + 1)];
                unite(i + 1, i);
            }
            if (left <= nums[i]) ans += (size_l + 1) * (size_r + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution795 solu;
    cout << solu.numSubarrayBoundedMax(*new vector<int>{2,1,4,3}, 2, 3) << endl;
    cout << solu.numSubarrayBoundedMax_implementation2(*new vector<int>{2,1,4,3}, 2, 3) << endl;
    cout << solu.numSubarrayBoundedMax_implementation3(*new vector<int>{2,1,4,3}, 2, 3) << endl;
    cout << solu.numSubarrayBoundedMax_implementation4(*new vector<int>{2,1,4,3}, 2, 3) << endl;
    return 0;
}
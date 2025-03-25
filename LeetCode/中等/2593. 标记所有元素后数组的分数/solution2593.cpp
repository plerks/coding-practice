/*
url: https://leetcode.cn/problems/find-score-of-an-array-after-marking-all-elements/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2593 {
public:
    // 直接模拟，时间复杂度O(nlogn)，主要在排序
    long long findScore(vector<int>& nums) {
        int n = nums.size();
        long long score = 0;
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        stable_sort(idx.begin(), idx.end(), [&](const int x, const int y) { // 这里要用stable_sort，题目要求如果有相等元素，选择下标最小的一个并标记左右
            return nums[x] < nums[y];
        });
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (vis[idx[i]]) continue;
            score += nums[idx[i]];
            vis[idx[i]] = true;
            if (idx[i] - 1 >= 0) vis[idx[i] - 1] = true;
            if (idx[i] + 1 < n) vis[idx[i] + 1] = true;
        }
        return score;
    }

    /* 参考灵茶题解，
    从左往右遍历，当右边有更小的数时，应当优先继续往右走，从更小的数开始选，因此，用分组循环找递减段[start, i]，
    找到坡底之后，i, i - 2, i - 4 ... 依次可选，然后i + 1被i标记，从i + 2开始
    */
    long long findScore_implementation2(vector<int>& nums) {
        int n = nums.size();
        long long score = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (; i + 1 < n && nums[i + 1] < nums[i]; i++);
            /* 1 5 4 3，1标记了5，会不会从3开始往左走的末尾把5给加到score里了？
            否，1选了之后i += 2了，5不会在[start, i]的范围里
            */
            for (int j = i; j >= start; j -= 2) {
                score += nums[j];
            }
            i += 2;
        }
        return score;
    }
};

int main(int argc, char const *argv[]) {
    Solution2593 solu;
    cout << solu.findScore(*new vector<int>{2,1,3,4,5,2}) << endl;

    cout << solu.findScore_implementation2(*new vector<int>{2,1,3,4,5,2}) << endl;
    return 0;
}
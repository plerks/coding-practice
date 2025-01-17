/*
url: https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/description/
参考: https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/solutions/2528771/jiao-ni-yi-ci-xing-ba-dai-ma-xie-dui-on-zuspx/
相关: LeetCode2953. 统计完全子字符串
标签: 分组循环
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2760 {
public:
    // 分组循环: 数组按一定条件分割为互不相交的组时(相邻段的端点可能重合)，怎么写把这些组拿出来
    // 分组循环时间复杂度是O(n)
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int n = nums.size();
        int ans = 0;
        
        int i = 0;
        while (i < n) {
            if (nums[i] % 2 == 1 || nums[i] > threshold) {
                i++;
                continue;
            }
            int start = i; // 记录这个段的开头位置
            i++; // 开头位置已满足，从下一个位置开始判断
            while (i < n && nums[i] <= threshold && nums[i - 1] % 2 != nums[i] % 2) {
                i++;
            }
            // 这时i - 1合法，i不合法，[start, i - 1]为合法段。且下一轮开始时i就是新一轮的开头
            ans = max(ans, i - start);
        }
        return ans;
    }

    // 极简写法，推荐
    int longestAlternatingSubarray_implementation2(vector<int>& nums, int threshold) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n;) {
            if (nums[i] % 2 == 1 || nums[i] > threshold) {
                i++;
                continue;
            }
            int start = i; // 记录这个段的开头位置
            // 开头位置已满足，从下一个位置开始判断，要先i++
            for (i++; i < n && nums[i] <= threshold && nums[i - 1] % 2 != nums[i] % 2; i++); // 注意这里for循环直接结束
            // [start, i - 1]为合法段
            ans = max(ans, i - start);
        }
        return ans;
    }

    // 双指针的写法思路，容易出bug，特别是越界的问题
    int longestAlternatingSubarray_implementation3(vector<int>& nums, int threshold) {
        int n = nums.size();
        int ans = 0;

        int i = 0, j = 0;
        // [i, j]作为当前段，要么j向右扩展，要么收缩为空区间
        while (j < n) {
            if (nums[j] % 2 == 1 || nums[j] > threshold) {
                j++;
                i = j; // i直接移到j处
                continue;
            }
            j++;
            while (j < n && nums[j] <= threshold && nums[j - 1] % 2 != nums[j] % 2) {
                j++;
            }
            // [i, j - 1]为合法段
            ans = max(ans, j - i);
            i = j; // 注意这里得手动开启下一段
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2760 solu;
    cout << solu.longestAlternatingSubarray(*new vector<int>{3,2,5,4}, 5) << endl;
    cout << solu.longestAlternatingSubarray_implementation2(*new vector<int>{3,2,5,4}, 5) << endl;

    cout << solu.longestAlternatingSubarray_implementation3(*new vector<int>{3,2,5,4}, 5) << endl;
    cout << solu.longestAlternatingSubarray_implementation3(*new vector<int>{2,3,4,5}, 4) << endl;
    cout << solu.longestAlternatingSubarray_implementation3(*new vector<int>{2,2}, 18) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution80 {
public:
    // 我的解法，用分组循环
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int index = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && nums[i] == nums[i - 1]; i++);
            if (i - start == 1) nums[index++] = nums[start];
            else {
                nums[index++] = nums[start];
                nums[index++] = nums[start];
            }
        }
        return index;
    }

    // 灵茶题解解法，更简洁。把nums左侧|->当做一个栈，index指向待写入的栈顶，观察index - 2位置是否是当前的nums[i]，若是则说明已经有2个了
    int removeDuplicates_implementation2(vector<int>& nums) {
        int n = nums.size();
        int index = 2; // 从2开始
        for (int i = 2; i < n; i++) {
            if (nums[index - 2] != nums[i]) {
                nums[index++] = nums[i];
            }
        }
        return min(index, n); // index从2开始，取min处理[1]这样的特殊用例
    }
};

int main(int argc, char const *argv[]) {
    Solution80 solu;
    cout << solu.removeDuplicates(*new vector<int>{1,1,1,2,2,3}) << endl;
    // cout << solu.removeDuplicates_implementation2(*new vector<int>{1,1,1,2,2,3}) << endl;
    cout << solu.removeDuplicates_implementation2(*new vector<int>{1,2}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution167 {
public:
    /* 最开始确定正解在[0, n - 1]内，每次指针的移动不会错过正解，
    当l / r先到达正解位置，则性质保证了这时另一端会连续单调移动到正解位置。
    */
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        int l = 0, r = n - 1;
        while (l < r) {
            if (numbers[l] + numbers[r] == target) break;
            else if (numbers[l] + numbers[r] < target) {
                l++;
            }
            else r--;
        }
        return {l + 1, r + 1};
    }
};

int main(int argc, char const *argv[]) {
    Solution167 solu;
    auto a = solu.twoSum(*new vector<int>{2,7,11,15}, 9);
    return 0;
}
/*
url: https://leetcode.cn/problems/find-the-smallest-divisor-given-a-threshold/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1283 {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        // 题目保证一定有解
        int mx = *max_element(nums.begin(), nums.end());

        auto check = [&](int mid) {
            int sum = 0;
            for (int x : nums) {
                sum += (x - 1) / mid + 1;
            }
            return sum <= threshold;
        };

        int left = 1, right = mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution1283 solu;
    cout << solu.smallestDivisor(*new vector<int>{1,2,5,9}, 6) << endl;
    return 0;
}
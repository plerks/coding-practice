/*
url: https://leetcode.cn/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/
标签: LeetCode第416场周赛, 二分
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3296 {
public:
    // 二分套二分
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // 从否到是，搜索第一个是
        long long mx = *max_element(workerTimes.begin(), workerTimes.end());
        long long left = 0;
        long long right = mountainHeight * (long long)(1 + mountainHeight) * mx;
        while (left <= right) {
            long long mid = (left + right) / 2; // 工作时间
            long long deHeight = 0;
            for (auto &w : workerTimes) {
                // 计算mid时间，工人i能让山下降的高度
                long long lo = 0;
                long long hi = mountainHeight;
                while (lo <= hi) {
                    long long mi = (lo + hi) / 2;
                    if (w * (1 + mi) * mi <= 2 * mid) {
                        lo = mi + 1;
                    }
                    else {
                        hi = mi - 1;
                    }
                }
                deHeight += lo - 1;
            }
            if (deHeight >= mountainHeight) {
                right = mid - 1;
            }
            else left = mid + 1;
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution3296 solu;
    int mountainHeight = 4;
    vector<int> workTimes = {2,1,1};
    cout << solu.minNumberOfSeconds(mountainHeight, workTimes) << endl;
    return 0;
}

/*
url: https://leetcode.cn/problems/count-pairs-that-form-a-complete-day-i/description/
标签: LeetCode第402场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3184 {
public:
    // 数据范围小，直接暴力模拟即可
    int countCompleteDayPairs(vector<int>& hours) {
        int n = hours.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((hours[i] + hours[j]) % 24 == 0) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

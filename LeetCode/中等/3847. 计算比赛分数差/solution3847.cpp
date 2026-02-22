/*
url: https://leetcode.cn/problems/find-the-score-difference-in-a-game/
标签: LeetCode第490场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3847 {
public:
    int scoreDifference(vector<int>& nums) {
        int n = nums.size();
        int score[2]; score[0] = score[1] = 0;
        int p = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 1) p ^= 1;
            if ((i + 1) % 6 == 0) p ^= 1;
            score[p] += nums[i];
        }
        return score[0] - score[1];
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
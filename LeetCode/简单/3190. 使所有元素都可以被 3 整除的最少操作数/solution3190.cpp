/*
url: https://leetcode.cn/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/
标签: LeetCode第133场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3190 {
public:
    int minimumOperations(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            int c = num / 3;
            ans += min(num - c * 3, (c + 1) * 3 - num);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

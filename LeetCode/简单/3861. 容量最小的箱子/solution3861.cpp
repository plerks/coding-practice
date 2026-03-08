/*
url: https://leetcode.cn/problems/minimum-capacity-box/
标签: LeetCode第492场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3861 {
public:
    int minimumIndex(vector<int>& capacity, int itemSize) {
        int n = capacity.size();
        int ans = -1;
        int min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (capacity[i] >= itemSize && capacity[i] < min) {
                min = capacity[i];
                ans = i;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
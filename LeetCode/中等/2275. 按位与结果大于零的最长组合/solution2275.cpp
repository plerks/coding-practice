// https://leetcode.cn/problems/largest-combination-with-bitwise-and-greater-than-zero/description/?envType=daily-question&envId=2025-01-12

#include <bits/stdc++.h>

using namespace std;

class Solution2275 {
public:
    int largestCombination(vector<int>& candidates) {
        // 1 <= candidates[i] <= 10^7
        /* 这题是子序列，不是子数组，所以不能滑窗。
        按位&会越来越小，最后>0得某一位上全是1，所以哪一位上1最多就是最长选择
        */
        int cnt[32]{};
        for (int x : candidates) {
            for (int i = 0; i < 32; i++) {
                cnt[i] += (x >> i) & 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            ans = max(ans, cnt[i]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2275 solu;
    cout << solu.largestCombination(*new vector<int>{16,17,71,62,12,24,14}) << endl;
    return 0;
}
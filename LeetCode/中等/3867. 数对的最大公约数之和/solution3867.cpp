// https://leetcode.cn/problems/sum-of-gcd-of-formed-pairs/

#include <bits/stdc++.h>

using namespace std;

class Solution3867 {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        using i64 = long long;
        vector<i64> prefixGcd(n);
        prefixGcd[0] = nums[0];
        i64 mx = nums[0];
        for (int i = 1; i < n; i++) {
            mx = max(mx, (i64)nums[i]);
            prefixGcd[i] = __gcd((i64)nums[i], mx);
        }
        sort(prefixGcd.begin(), prefixGcd.end());
        int l = 0, r = n - 1;
        i64 ans = 0;
        while (l < r) {
            ans += __gcd(prefixGcd[l], prefixGcd[r]);
            l++, r--;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
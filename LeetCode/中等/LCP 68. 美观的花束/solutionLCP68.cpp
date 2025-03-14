/*
url: https://leetcode.cn/problems/1GxJYY/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class SolutionLCP68 {
public:
    int beautifulBouquet(vector<int>& flowers, int cnt) {
        int n = flowers.size();
        const int MOD = 1000000007;
        int ans = 0;
        unordered_map<int, int> freq;
        int illegal = 0; // 出现次数超过cnt的种类数
        for (int l = 0, r = 0; r < n; r++) {
            freq[flowers[r]]++;
            if (freq[flowers[r]] > cnt) illegal++;
            while (illegal > 0) {
                freq[flowers[l]]--;
                if (freq[flowers[l]] == cnt) illegal--;
                l++;
            }
            ans = (ans + r - l + 1) % MOD;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    SolutionLCP68 solu;
    cout << solu.beautifulBouquet(*new vector<int>{1,2,3,2}, 1) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/number-of-excellent-pairs/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2354 {
public:
    /* 参考灵茶题解，从集合论的角度看，|A ∪ B| + |A ∩ B| = |A| + |B|；
    也可以列真值表来证。
    */
    long long countExcellentPairs(vector<int>& nums, int k) {
        unordered_set<int> st;
        for (int x : nums) st.insert(x);
        int map[32]{}; // (1的个数, 数的个数)
        for (int x : st) {
            map[__builtin_popcount(x)]++;
        }
        int suf[33]{}; // map的后缀和
        for (int i = 31; i >= 0; i--) {
            suf[i] = suf[i + 1] + map[i];
        }
        long long ans = 0;
        for (int i = 0; i <= 31; i++) { // (a, b)，枚举a，i表示a的1的个数
            int c = map[i];
            if (c > 0) {
                int j = k - i;
                j = max(0, j); // 若 i 过大，则 j 只需 > 0 个 1，这里防止 j 为负数
                if (j > 31) continue;
                ans += c * suf[j];
            }   
        }
        return ans;
    }
    
    // 灵茶题解写法
    long long countExcellentPairs_implementation2(vector<int>& nums, int k) {
        const int U = 31;
        int map[U]{};
        for (int x : unordered_set<int>(nums.begin(), nums.end())) {
            map[__builtin_popcount(x)]++;
        }

        int s = 0;
        for (int i = k; i < U; i++) s += map[i]; // [k, ..) 的后缀和，表示 1 足够多的数的个数

        long long ans = 0;
        for (int cx = 0; cx < U; cx++) {
            ans += map[cx] * s;
            int cy = k - (cx + 1);
            if (0 <= cy && cy < U) s += map[cy]; // 累加后缀和
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2354 solu;
    cout << solu.countExcellentPairs(*new vector<int>{1,2,3,1}, 3) << endl;

    cout << solu.countExcellentPairs_implementation2(*new vector<int>{1,2,3,1}, 3) << endl;
    return 0;
}
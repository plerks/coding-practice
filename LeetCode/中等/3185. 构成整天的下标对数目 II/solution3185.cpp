/*
url: https://leetcode.cn/problems/count-pairs-that-form-a-complete-day-ii/description/
标签: LeetCode第402场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3185 {
public:
    /* hours[i] + hours[j]是24的倍数 等价于 hours[i] + hours[j] % 24 = 0，于是只需考虑hours[i]和hours[j]对24的余数即可。
    一开始没想到这个等价，还想着需要考虑到底是24的几倍，这样写肯定也会超时，先写的第三题再回来做第二题的。
    */
    long long countCompleteDayPairs(vector<int>& hours) {
        unordered_map<int, int> map;
        int n = hours.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int hour = hours[i];
            int r = hour % 24;
            ans += map[(24 - r) % 24];
            map[r]++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

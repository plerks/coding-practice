/*
url: https://leetcode.cn/problems/friends-of-appropriate-ages/
标签: 【题单】滑动窗口与双指针, 考虑值域, 值域计数
*/
#include <bits/stdc++.h>

using namespace std;

class Solution825 {
public:
    // 我的解法，时间复杂度O(nlogn)，主要时间在排序上
    int numFriendRequests(vector<int>& ages) {
        /* 以x为视角，要向某个y发消息的条件是，0.5 * age[x] + 7 < age[y] <= age[x] && (age[y] <= 100 || age[x] >= 100)
        如果age[x] >= 100，那么只需要看前一个条件，否则，说明age[x] < 100，则条件要为真，必须要age[y] <= 100，而只要age[y] <= age[x]即可满足
        这个条件，所以也是只需要看前面那个条件。综上，(age[y] <= 100 || age[x] >= 100)这个条件没用。
        */
        int n = ages.size();
        sort(ages.begin(), ages.end());
        int l1 = 0, l2 = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            while (l1 < n && ages[l1] * 2 <= ages[r] + 14) l1++;
            while (l2 < n && ages[l2] <= ages[r]) l2++;
            // 这里的l2 - l1 - 1，合法区间是[l1, l2)，区间长度是l2 - l1，但是如果区间包含自己(r)，要再减去1
            if (l2 - l1 < 0) continue; // 一个坑，区间长为负数时跳过，这题区间为空时不一定是l2 == l1(区间长为0)，可能l1还会更大，l2 - l1就为负了。不处理的话后面会加了个负数而不是0(也可以后面把要加的值和0取max)
            if (l1 <= r && r < l2) ans += l2 - l1 - 1;
            else ans += l2 - l1;
        }
        return ans;
    }

    // 灵茶题解解法，这题值域小，1 <= ages[i] <= 120，所以把ages在值域上计数，时间复杂度O(n + U)，U为max(ages)
    int numFriendRequests_implementation2(vector<int>& ages) {
        int cnt[121]{};
        for (int age : ages) cnt[age]++;
        int ans = 0;
        int sum = 0;
        for (int l = 0, r = 0; r < 121; r++) {
            sum += cnt[r];
            while (l * 2 <= r + 14) {
                sum -= cnt[l];
                l++;
            }
            if (sum > 0) ans += (sum - 1) * cnt[r]; // 窗口总共sum人，r位置上的人可以与其余sum - 1人配对。sum为0时，ans应该加0，如果不判断的话ans会加负数变小
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution825 solu;
    // cout << solu.numFriendRequests(*new vector<int>{16,17,18}) << endl;
    // cout << solu.numFriendRequests(*new vector<int>{108,115,5,24,82}) << endl;
    // cout << solu.numFriendRequests(*new vector<int>{101,98,80,20,1,97,3,77,114,109}) << endl;

    cout << solu.numFriendRequests_implementation2(*new vector<int>{16,17,18}) << endl;
    return 0;
}
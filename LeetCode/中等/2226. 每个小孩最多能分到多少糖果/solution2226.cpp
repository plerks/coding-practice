/*
url: https://leetcode.cn/problems/maximum-candies-allocated-to-k-children/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2226 {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        int n = candies.size();
        long long sum = accumulate(candies.begin(), candies.end(), 0LL);

        auto check = [&](int x) {
            long long cnt = 0;
            for (int c : candies) {
                cnt += c / x;
            }
            return cnt >= k;
        };

        long long left = 1, right = sum / k;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
};

int main(int argc, char const *argv[]) {
    Solution2226 solu;
    // cout << solu.maximumCandies(*new vector<int>{5,8,6}, 3) << endl;
    cout << solu.maximumCandies(*new vector<int>{1,2,3,4,10}, 5) << endl;
    return 0;
}
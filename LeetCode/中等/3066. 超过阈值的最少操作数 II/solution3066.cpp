// https://leetcode.cn/problems/minimum-operations-to-exceed-threshold-value-ii/description/?envType=daily-question&envId=2025-01-15

#include <bits/stdc++.h>

using namespace std;

class Solution3066 {
public:
    int minOperations(vector<int>& nums, int k) {
        int ans = 0;
        priority_queue<long long, vector<long long>, greater<long long>> q(nums.begin(), nums.end());
        // 题目保证最终一定能让数字都>=k
        while (q.top() < k && q.size() >= 2) {
            long long x = q.top(); q.pop();
            long long y = q.top(); q.pop();
            ans++;
            q.push((min(x, y) << 1) + (long long)max(x, y));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3066 solu;
    cout << solu.minOperations(*new vector<int>{2,11,10,1,3}, 10) << endl;
    cout << solu.minOperations(*new vector<int>{1,1,2,4,9}, 20) << endl;
    return 0;
}
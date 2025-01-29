/*
url: https://leetcode.cn/problems/minimum-cost-to-make-arrays-identical/
标签: LeetCode第148场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3424 {
public:
    /* 这题理解错了意思，一直以为是每切一刀的开销都要k，但是题目是切的话要开销k，但是可以任意刀，
    最后才发现意思不对。
    关于配对方式，应该让arr和brr的大的和大的配对，小的和小的配对，证明方式可以用局部调整法，(灵茶题解中称为交换论证法)，
    具体来说就是 a[0] a[1] 和 b[0] b[1]，如果让 a[0]和b[1] 配对，a[1]和b[0] 配对，代价会更大(可以通过考虑大小情况证明)，
    所以局部要小小大大配对，于是所有地方都得这样，整体也就是小小大大配对。
    */
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        int n = arr.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(arr[i] - brr[i]);
        }
        long long other = k;
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        for (int i = 0; i < n; i++) {
            other += abs(arr[i] - brr[i]);
        }
        return min(ans, other);
    }
};

int main(int argc, char const *argv[]) {
    Solution3424 solu;
    cout << solu.minCost(*new vector<int>{-7,9,5}, *new vector<int>{7,-2,-5}, 2) << endl;
    return 0;
}
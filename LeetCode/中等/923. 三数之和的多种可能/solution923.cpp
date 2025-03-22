/*
url: https://leetcode.cn/problems/3sum-with-multiplicity/
相关: LeetCode15. 三数之和
标签: 【题单】滑动窗口与双指针, 恰好型滑动窗口, 滑动过程中计数, 考虑值域, 值域计数
*/
#include <bits/stdc++.h>

using namespace std;

class Solution923 {
public:
    /* 临界情况 arr[j] + arr[k] == target，k增大，j就减小，相向双指针。可以用恰好型滑动窗口做，也可以滑动过程中计数。
    但是由于有重复元素，例如[1,2,2,5,5]，当i在arr[0]时，以第一层循环枚举k为例，当k在arr[4]时，内循环结束时j已经移动到了arr[3]，
    然后k到3，这时，两个2 + arr[3]就没有计数。所以，有重复元素得值域计数。
    */
    int threeSumMulti_wa(vector<int>& arr, int target) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int t = target - arr[i];
            // 
            int j = i + 1;
            for (int k = n - 1; k > i + 1; k--) {
                while (j < k) {
                    int sum = arr[j] + arr[k];
                    if (sum == t) {
                        ans++;
                        j++;
                    }
                    else if (sum < t) j++;
                    else break;
                }
            }
        }
        return ans;
    }

    int threeSumMulti(vector<int>& arr, int target) {
        long long ans = 0;
        const int mod = 1e9 + 7;
        int N = 100; // 0 <= arr[i] <= 100
        vector<int> cnt(N + 1); // 值域计数去重
        for (int x : arr) cnt[x]++; 
        
        for (int i = 0; i <= N; i++) {
            int k = N;
            for (int j = i; j <= N; j++) {
                while (k >= j) {
                    int sum = i + j + k;
                    if (sum == target) {
                        // (a, a, a)
                        if (i == j && j == k) {
                            ans += 1LL * cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6; // (cnt[i] - 2)可能为负，但会由(cnt[i] - 1)保证加上的是0
                        }
                        else if (i == j) { // (a, a, b)
                            ans += 1LL * cnt[i] * (cnt[i] - 1) * cnt[k] / 2;
                        }
                        else if (i == k) { // (a, b, a)
                            ans += 1LL * cnt[i] * cnt[j] * (cnt[k] - 1) / 2;
                        }
                        else if (j == k) { // (b, a, a)
                            ans += 1LL * cnt[i] * cnt[j] * (cnt[k] - 1) / 2;
                        }
                        else ans += 1LL * cnt[i] * cnt[j] * cnt[k]; // (a, b, c)

                        ans %= mod;
                        k--;
                    }
                    else if (sum > target) k--;
                    else break;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution923 solu;
    cout << solu.threeSumMulti(*new vector<int>{1,1,2,2,3,3,4,4,5,5}, 8) << endl;
    return 0;
}
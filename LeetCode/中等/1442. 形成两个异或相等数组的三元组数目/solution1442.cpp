/*
url: https://leetcode.cn/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1442 {
public:
    // 时间复杂度O(n^3)
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] ^ arr[i];
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j; k < n; k++) {
                    // [i, j) [j, k]
                    if ((pre[j - 1 + 1] ^ pre[i - 1 + 1]) == (pre[k + 1] ^ pre[j - 1 + 1])) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }

    // 优化一下，xor[i, j) == xor[j, k]，那么就是 xor[i, k] == 0，然后中间选个j。i < j <= k。j范围为(i, k]
    // 时间复杂度O(n^2)
    int countTriplets_implementation2(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int sum = arr[i];
            for (int k = i + 1; k < n; k++) {
                sum ^= arr[k];
                if (sum == 0) ans += k - i;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1442 solu;
    cout << solu.countTriplets(*new vector<int>{2,3,1,6,7}) << endl;

    cout << solu.countTriplets_implementation2(*new vector<int>{2,3,1,6,7}) << endl;
    return 0;
}
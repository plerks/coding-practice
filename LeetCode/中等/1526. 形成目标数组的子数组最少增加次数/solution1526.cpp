/*
url: https://leetcode.cn/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/description/
参考: https://leetcode.cn/problems/minimum-operations-to-make-array-equal-to-target/solutions/2851722/chai-fen-shu-zu-fen-lei-tao-lun-pythonja-f8lo/
相关: LeetCode3229. 使数组等于目标数组所需的最少操作次数
标签: 差分数组, 贪心, 子数组
*/

// `LeetCode3229. 使数组等于目标数组所需的最少操作次数`用到此题

#include <bits/stdc++.h>

using namespace std;

class Solution1526 {
public:
    // `LeetCode3229. 使数组等于目标数组所需的最少操作次数`中的两种做法
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = target[i] - (i - 1 >= 0 ? target[i - 1] : 0);
        }
        int ans = 0;
        int s = 0;
        for (int i = 0; i < n; i++) {
            int k = diff[i];
            if (k > 0) {
                if (s < 0) {
                    ans += max(k + s, 0);
                }
                else ans += k;
            }
            else {
                if (s > 0) {
                    ans -= min(k + s, 0);
                }
            }
            s += k;
        }
        return ans;
    }

    int minNumberOperations_implementation2(vector<int>& target) {
        int n = target.size();
        vector<int> diff(n + 1);
        for (int i = 0; i < n; i++) {
            diff[i] = target[i] - (i - 1 >= 0 ? target[i - 1] : 0);
        }
        diff[n] = -target[n - 1];
        int ans = 0;
        for (int d : diff) {
            if (d > 0) ans += d;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1526 solu;
    vector<int> target = {1,2,3,2,1};
    cout << solu.minNumberOperations(target) << endl;
    cout << solu.minNumberOperations_implementation2(target) << endl;
    return 0;
}

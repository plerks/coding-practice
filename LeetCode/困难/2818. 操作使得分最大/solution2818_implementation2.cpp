/*
url: https://leetcode.cn/problems/apply-operations-to-maximize-score/
参考: https://leetcode.cn/problems/apply-operations-to-maximize-score/solutions/2385936/gong-xian-fa-dan-diao-zhan-pythonjavacgo-23c4/
标签: 【算法题单】单调栈, 贡献法, 质因数分解
*/

#include <bits/stdc++.h>

using namespace std;

// 参考灵茶题解，可以预处理1e5以内的数的“质数分数”，方式类似筛，或者说刷表法

const int MX = 1e5 + 1;

int omega[MX]; // 小omega函数，表示n的不同质因数个数

auto init = []() {
    for (int i = 2; i < MX; i++) {
        if (omega[i] == 0) { // i是质数
            for (int j = i; j < MX; j += i) {
                omega[j]++; // i是j的一个质因子
            }
        }
    }
    return 0;
}();

const int MOD = 1e9 + 7;

class Solution2818 {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> left(n); // 如果多个元素质数分数相同且最高，选择下标最小的一个。所以往左不能包含相等，找左侧第一个 >=
        vector<int> right(n, n); // 右侧第一个 >
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && omega[nums[st.top()]] < omega[nums[i]]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        vector<int> idx(n); // 标号数组
        iota(idx.begin(), idx.end(), 0);
        stable_sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums[i] > nums[j];
        });

        long long ans = 1;

        // 以nums[p]为质数分数最高的元素，有 (right - p) * (p - left) 个子数组
        for (int i = 0; i < n; i++) {
            if (k <= 0) break;
            long long p = idx[i];
            long long cnt = (right[p] - p) * (p - left[p]);
            long long pick = min(cnt, (long long)k); // 选pick个
            ans = ans * fastPow(nums[p], pick) % MOD;
            k -= pick;
        }

        return ans % MOD;
    }

    long long fastPow(long long a, long long b) {
        long long res = 1;
        while (b > 0) {
            if ((b & 1) != 0) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution2818 solu;
    cout << solu.maximumScore(*new vector<int>{8,3,9,3,8}, 2) << endl;
    cout << solu.maximumScore(*new vector<int>{19,12,14,6,10,18}, 3) << endl;
    return 0;
}
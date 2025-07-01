/*
url: https://leetcode.cn/problems/neighboring-bitwise-xor/
相关: LeetCode1734. 解码异或后的排列
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2683 {
public:
    bool doesValidArrayExist(vector<int>& derived) {
        // derived 中的值不是 0 就是 1。所以虽然依赖关系成环了，但是可以选一个起点枚举其值
        int n = derived.size();
        vector<int> ans(n);
        ans[0] = 0;

        auto check = [&]() {
            for (int i = 1; i < n; i++) {
                ans[i] = ans[i - 1] ^ derived[i - 1];
            }
            return ans[n - 1] ^ ans[0] == derived[n - 1];
        };

        if (check()) return true;
        ans[0] = 1;
        return check();
    }

    // 参考灵茶题解，有更好的做法，ans[n - 1] ^ ans[0] == derived[n - 1] 的判断，把ans[n - 1]展开，
    // 简化为判断 a[0] ^ d[0] ^ ... ^ d[n - 2] == d[n - 1]
    bool doesValidArrayExist_implementation2(vector<int>& derived) {
        int xor_ = 0; // xor是c++关键字，是^的备选拼写
        for (auto &x : derived) {
            xor_ ^= x;
        }
        return xor_ == 0;
    }
};

int main(int argc, char const *argv[]) {
    Solution2683 solu;
    cout << solu.doesValidArrayExist(*new vector<int>{1,1,0}) << endl;
    return 0;
}
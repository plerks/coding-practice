/*
url: https://leetcode.cn/problems/defuse-the-bomb/description/
参考: https://leetcode.cn/problems/defuse-the-bomb/solutions/2765762/on-ding-chang-hua-dong-chuang-kou-python-y2py/
标签: 【题单】滑动窗口与双指针, 定长滑窗的写法技巧, 定长滑动窗口的写法技巧
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1652 {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> ans(n, 0);
        if (k == 0) return ans;
        int left = 0, right = 1;
        int sum = 0;
        if (k < 0) reverse(code.begin(), code.end());
        while (left < n) {
            sum += code[right];
            if (right >= left && right - left != abs(k)) { // 滑窗初始化
                right = (right + 1) % n;
            }
            else { // (left, right]长度为k
                ans[left] = sum;
                sum -= code[(left + 1 + n) % n];
                left++;
                right = (right + 1 + n) % n;
            }
        }
        if (k < 0) reverse(ans.begin(), ans.end());
        return ans;
    }

    // 灵茶山艾府题解写法，更简洁
    vector<int> decrypt_implementation2(vector<int>& code, int k) {
        int n = code.size();
        vector<int> ans(n, 0);
        if (k == 0) return ans;
        int right = k > 0 ? k + 1 : n; // 注意这里right的选取，不管k正负都是右边界(右边下一个要进入的元素)
        k = abs(k);
        // 把定长滑窗的初始化单独做，也不用非要惦记着合到一起
        int sum = std::accumulate(code.begin() + right - k, code.begin() + right, 0);
        for (int i = 0; i < n; i++) {
            ans[i] = sum;
            sum += code[right % n] - code[(right - k) % n];
            right++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1652 solu;
    auto a = solu.decrypt(*new vector<int>{2,4,9,3}, -2);
    auto b = solu.decrypt_implementation2(*new vector<int>({2,4,9,3}), -2);
    return 0;
}
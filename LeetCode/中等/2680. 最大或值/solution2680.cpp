/*
url: https://leetcode.cn/problems/maximum-or/
参考: https://leetcode.cn/problems/maximum-or/solutions/2268795/tan-xin-qian-hou-zhui-fen-jie-pythonjava-wrv1/
标签: 【算法题单】位运算, 前后缀分解, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2680 {
public:
    // 肯定把k次全用在最高的那个1上，让它跑最远。但是[12, 9]这个用例可以看出，有多个最高1时，要选择到底是哪个来移动
    // 枚举x，并把x <<= k，然后怎么快速计算nums的总& ?
    // 参考LeetCode的提示功能，前后缀分解
    long long maximumOr(vector<int>& nums, int k) {
        // 1 <= k <= 15
        int n = nums.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] | nums[i];
        
        long long ans = 0;
        long long suf = 0;
        for (int i = n - 1; i >= 0; i--) {
            ans = max(ans, pre[i - 1 + 1] | ((long long)nums[i] << k) | suf);
            suf |= nums[i];
        }
        return ans;
    }

    /* 参考灵茶题解，先计算nums所有元素的or结果all_or。枚举x，能不能从all_or里把x摘出来？
    考虑 all_or ^ x，
    all_or中原本为0的位，x一定也为0(或的性质)，计算正确。

    all_or中原本为1的位，^x之后的结果却不一定对，比如x这一位上为1，^x变成0，但是还有其它元素这一位为1，正常应该为1
    （all_or ^ x的结果，与正确的{nums} - {x}的OR结果，只有该是1，算成0这一种错误情况）。
    所以，all_or ^ x 不能正确地将x摘出来，all_or里为0的位^x之后是对的，为1的位则不一定，可能从正确的1变成错误的0了。
    但是这题还有修复的办法，既然是或，且只有1的位置不对，只需要知道 {nums} - {x} 的某一位上是否有 > 0 个1就行了(也即nums中这一位1的个数是否 > 1)。
    这样就知道 all_or 的1该不该继续保持为1，就能知道{nums} - {x} OR的正确结果了。
    */
    long long maximumOr_implementation2(vector<int>& nums, int k) {
        int all_or = 0, fixed = 0;
        for (int x : nums) {
            // 如果此时 all_or 和 x 有公共的1，那么nums中这一位有 > 1 个1，记到fixed中，这一位一定为1
            fixed |= all_or & x;
            all_or |= x;
        }

        long long ans = 0;
        for (int x : nums) {
            ans = max(ans, (all_or ^ x) | fixed | ((long long)x << k));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2680 solu;
    cout << solu.maximumOr(*new vector<int>{12,9}, 1) << endl;

    cout << solu.maximumOr_implementation2(*new vector<int>{12,9}, 1) << endl;
    return 0;
}
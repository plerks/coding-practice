/*
url: https://leetcode.cn/problems/count-number-of-maximum-bitwise-or-subsets/
参考: https://leetcode.cn/problems/count-number-of-maximum-bitwise-or-subsets/solutions/1338209/by-ac_oier-dos6/
标签: 【算法题单】位运算, 状态压缩, 状压dp
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2044 {
public:
    /* 这题 1 <= nums.length <= 16，所以暴力枚举所有子集可能也能过，不过太暴力了？否，countMaxOrSubsets_implementation3()，直接用dfs没直觉上那么暴力
    宫水三叶题解解法一，状态压缩。枚举nums的元素选取状态可以用一个二进制int来表示(<= 2^n - 1)，然后就可以用二进制的int来枚举
    
    时间复杂度 O(2^n * n)
    */
    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();
        int mx = 0, cnt = 0;
        for (int s = 1; s < (1 << n); s++) { // s从1开始，不考虑空集
            int or_ = 0; // s对应选取方案的or结果
            for (int i = 0; i < n; i++) {
                if ((s >> i) & 1) {
                    or_ |= nums[i];
                }
            }
            if (or_ > mx) {
                mx = or_;
                cnt = 1;
            }
            else if (or_ == mx) cnt++;
        }
        return cnt;
    }

    /* 宫水三叶题解解法二，状压dp，上一种解法，内层为了计算一个选取方案state对应的或值，遍历了一遍nums计算，
    这个可以用dp优化。
    举例来说，一个state中选了多个数，考虑拿掉lowbit所代表的数，f[state] = f[state - lowbit] | nums[index of lowbit]，
    只要从小到大枚举state，就可以用 更小的state + 拆出来的一个位 计算当前state值了

    时间复杂度 O(2^n)
    */
    int countMaxOrSubsets_implementation2(vector<int>& nums) {
        int n = nums.size();
        int mx = 0, cnt = 0;
        vector<int> f(1 << n);
        for (int s = 1; s < (1 << n); s++) {
            // 计算 f[s]
            int prev = s & (s - 1);
            // cout << "__lg: " << (s & -s) << " " <<  __lg(s & -s) << endl;
            f[s] = f[prev] | nums[__lg(s & -s)]; // __lg(s & -s)代表当前s的lowbit代表nums的第几个元素
            if (f[s] > mx) {
                mx = f[s];
                cnt = 1;
            }
            else if (f[s] == mx) cnt++;
        }
        return cnt;
    }

    /* 宫水三叶题解解法三，这题用直接的dfs是可以的，不过要加一个参数记录前面元素的or值，比countMaxOrSubsets()的时间复杂度好，
    dfs的过程中能记录当前or结果，同样可以避免countMaxOrSubsets()一个个枚举状态要重新算一遍or的问题。
    */
    int countMaxOrSubsets_implementation3(vector<int>& nums) {
        int mx = 0, cnt = 0;

        auto dfs = [&](auto &dfs, int i, int val) -> void {
            if (i == nums.size()) { // 每位选/不选，现在得到了方案的值
                if (val > mx) {
                    mx = val;
                    cnt = 1;
                }
                else if (val == mx) cnt++;
            }
            else {
                dfs(dfs, i + 1, val);
                dfs(dfs, i + 1, val | nums[i]);
            }
        };
        
        dfs(dfs, 0, 0);
        return cnt;
    }
};

int main(int argc, char const *argv[]) {
    Solution2044 solu;
    cout << solu.countMaxOrSubsets(*new vector<int>{2,2,2}) << endl;
    cout << solu.countMaxOrSubsets(*new vector<int>{3,2,1,5}) << endl;

    cout << solu.countMaxOrSubsets_implementation2(*new vector<int>{2,2,2}) << endl;
    cout << solu.countMaxOrSubsets_implementation2(*new vector<int>{3,2,1,5}) << endl;

    cout << solu.countMaxOrSubsets_implementation3(*new vector<int>{2,2,2}) << endl;
    cout << solu.countMaxOrSubsets_implementation3(*new vector<int>{3,2,1,5}) << endl;
    return 0;
}
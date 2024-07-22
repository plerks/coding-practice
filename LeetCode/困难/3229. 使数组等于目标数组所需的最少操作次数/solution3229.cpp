/*
url: https://leetcode.cn/problems/minimum-operations-to-make-array-equal-to-target/
参考: https://www.bilibili.com/video/BV16Z421N7P2/
      https://leetcode.cn/problems/minimum-operations-to-make-array-equal-to-target/solutions/2851722/chai-fen-shu-zu-fen-lei-tao-lun-pythonja-f8lo/
相关: LeetCode3191. 使二进制数组全部等于 1 的最少操作次数 I, LeetCode3192. 使二进制数组全部等于 1 的最少操作次数 II, LeetCode1526. 形成目标数组的子数组最少增加次数
标签: 差分数组, 贪心, 子数组
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3229 {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = target[i] - nums[i];
        }
        // 问题转化成把arr变为全0
        /* 对特定的操作序列，操作结果与顺序无关，从左到右考虑操作。
        对于某个位置，前面i - 1位置被一些操作对应的子数组包括(i - 1作为子数组末尾)，那么是否要扩展到i位置？
        如果arr[i]比arr[i - 1]小且二者都为正，如4 2，则2这个位置可以直接利用4变为0中的两次即可顺便把2变成0、
        如果arr[i]比arr[i - 1]大且二者都为正，如4 6，则6这个位置也可以利用4变为0时的4次减
        如果都为负，则i位置需要的操作次数同样分析

        如果二者异号，则需要变化的方向不同，利用arr[i - 1]的变化只会起反作用，不利用

        归根结底，i位置可以考虑利用i - 1位置的变化来减少操作次数，关键是两个位置之间的差分

        对于4 -1 4 4，可不可以直接这样做：4 -1 4 4 -> 0 -5 0 0 -> 0 0 0 0?
        可以，这和代码的操作顺序不一样，但是操作次数都是9
        
        代码的操作顺序是，结果与操作顺序无关，考虑从左到右一个个完成变为0的操作，然后顺便考虑扩展借用i - 1的操作
        */
        long long ans = abs(arr[0]);
        for (int i = 1; i < n; i++) {
            if ((long long)arr[i - 1] * arr[i] <= 0) {
                ans += abs(arr[i]);
            }
            else {
                if (arr[i] > 0) {
                    if (arr[i] > arr[i - 1]) ans += arr[i] - arr[i - 1];
                }
                else {
                    if (arr[i] < arr[i - 1]) ans += arr[i - 1] - arr[i];
                }
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法一
    long long minimumOperations_implementation2(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> subtract(n);
        vector<int> diff(n);

        // 差值数组，问题等价于把差值变为0
        for (int i = 0; i < n; i++) {
            subtract[i] = target[i] - nums[i];
        }

        // 差分数组，问题等价于把差分数组变为0
        // 转化为对差分数组的操作之后，在差分数组的一个位置+1，对应要在后面一个位置-1，用s记录存起来的量，把s用在合适的地方
        for (int i = 0; i < n; i++) {
            diff[i] = subtract[i] - (i - 1 >= 0 ? subtract[i - 1] : 0);
        }

        long long ans = 0;
        long long s = 0; // 存着个s未用

        for (int i = 0; i < n; i++) {
            int k = diff[i];
            if (k > 0) {
                if (s < 0) { // 累计了对应的负的量，用上s
                    ans += max(k + s, 0LL); // 如果s负得厉害，只需要变为0就行，别变成负的
                }
                else ans += k;
            }
            else {
                if (s > 0) {
                    ans -= min(k + s, 0LL); // 如果s正得厉害，最多只加到0
                }
                else ans += -k;
            }
            s += k; // 无论哪种情况，存着的s的变化量都是k
        }
        return ans;
    }

    // 灵茶山艾府题解解法二
    long long minimumOperations_implementation3(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> subtract(n);
        vector<int> diff(n + 1);

        // 差值数组，问题等价于把差值变为0
        for (int i = 0; i < n; i++) {
            subtract[i] = target[i] - nums[i];
        }

        for (int i = 0; i < n; i++) {
            diff[i] = subtract[i] - (i - 1 >= 0 ? subtract[i - 1] : 0);
        }
        diff[n] = -subtract[n - 1]; // 注意差分数组最后要多一个位置

        long long ans = 0;

        // 差分数组n + 1个位置，对应的+1 -1操作最终会抵消，直接算正数之和即可(或者负数之和再取反)
        for (int d : diff) {
            if (d > 0) ans += d;
        }
        return ans;
    }
};

int main() {
    Solution3229 solu;
    /* vector<int> nums = {9,2,6,10,4,8,3,4,2,3};
    vector<int> target = {9,5,5,1,7,9,8,7,6,5}; */
    /* vector<int> nums = {4,4,1,1,2,5,5,1,1};
    vector<int> target = {3,2,3,4,5,2,3,3,4}; */
    vector<int> nums = {4,4,1,1};
    vector<int> target = {3,2,3,4};
    cout << solu.minimumOperations(nums, target) << endl;
    cout << solu.minimumOperations_implementation2(nums, target) << endl;
}
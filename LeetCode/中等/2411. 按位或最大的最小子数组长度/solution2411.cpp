/*
url: https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/
参考: https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/1830911/by-endlesscheng-zai1/
标签: 【算法题单】位运算, LogTrick
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2411 {
public:
    // 我的解法，不复用nums的空间的写法。枚举左端点，由于用了二分求最大值的位置，时间复杂度O(nlogn)。
    /* LogTrick：
        如何知道nums的所有(i, j)的 OR 的结果？
        以枚举左端点i为例，j要从i枚举到n - 1一个个算吗？
        原本是要这样，但是由于 OR 的特殊性，很快就可以跳出循环，不用再计算后面的。
        考虑上一轮我们已经求出了 or [i + 1, i + 1], [i + 1, i + 2], .. , [i + 1, n - 1] 的值，
        现在要求 or [i, i], [i, i + 1], [i, i + 2], .. , [i, n - 1] 的值，
        只多个 nums[i]，我们可以用上一轮的结果计算，而由于 OR 的特性：
        只要 nums[i] | [i + 1, i + x] 的值与上一轮的 [i + 1, i + x] 一样，那么右侧我们都不用计算了。为什么？
        因为 nums[i] | ... | nums[i + x] == nums[i + 1] | ... | nums[i + x]，那么对于更大的 y > x，
        一定也有 (nums[i] ... nums[i + x]) ... nums[i + y] == (nums[i + 1] ... nums[i + x]) ... nums[i + y]。
        右侧上一轮以nums[i + 1]为头的旧值，一定是这一轮以nums[i]为头的新值。不需要计算。
        本质原因在于，i中的1已经被[i + 1, i + x]中的1完全覆盖了，所以右侧不需要算了，i既未引入新的1，OR的结果一定是原来的值。

        注意，是省略了无需的计算，实际数组t里是有了以i为头，所有右端点位置的 OR 值的，相当于是全算出来了的。相当于用O(nlogU)时间把n^2个子数组的 OR 结果的
        unordered_set见了一遍。也说明了一个数组的所有子数组的 OR 值最多O(nlogU)个。
        
        那对每个i要计算的次数是多少？
        如果现在是 i 1000..1000 1100..1100 1110..1110
        那一轮i可能把每个右侧都计算一遍吗？
        可能，即变为 i 1001..1001 1101..1101 1111..1111，这轮i确实需要θ(n)时间
        但是整体考虑，每次需要往右继续算，意味着nums[i]多添了一个1，每个nums[j]最多添加1 32次就变成全1了，然后就一定能挡住往右算的企图。

        时间复杂度 O(nlogU)

        LogTrick能从O(n^2)优化到O(nlogU)的基础为，OR 运算性质特殊，每和一个数运算，只会往集合中添加1，每个nums[i]最多添加32次1。
    */
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> t(n); // t[j]表示当前轮遍历到的 i 到 j 位置的 OR 结果，or[i, j]。固定的是左端点
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if ((nums[i] | t[j]) == t[j]) { // j 无需计算，后面也无需计算了
                    break;
                }
                t[j] = nums[i] | t[j];
                // 到这里 t[j] 就更新为了以 i 打头的 [i, j] 或值了
            }
            // 现在t存了以i为头的所有子数组的OR值
            // t[j]表示[i, j]的or结果，有单调性，寻找第一个 >= t[n - 1] 的位置
            int index = lower_bound(t.begin() + i, t.end(), t.back()) - t.begin();
            ans[i] = index - i + 1;
        }
        return ans;
    }

    // 灵茶题解解法一，枚举右端点，然后用刷表法就能O(n)
    vector<int> smallestSubarrays_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) { // 枚举右端点
            ans[i] = 1;
            for (int j = i - 1; j >= 0 && (nums[i] | nums[j]) != nums[j]; j--) {
                nums[j] = nums[i] | nums[j]; // 复用nums，存or[j, i]的结果
                ans[j] = i - j + 1; // 刷表法
            }
        }
        return ans;
    }

    /* 灵茶题解解法二，维护去重后的 (值, 下标)，可以修改用来：
        1. 求出所有子数组的按位或的结果，以及值等于该结果的子数组的个数
        2. 求按位或结果等于任意给定数字的子数组的最短长度/最长长度
       方式是将以 nums[i] 为左端点的所有 (值, 下标) 去除重复值后记录起来。去重之后内层循环最多遍历 O(logU) 个元素。

       时间复杂度 O(nlogU)

       这是去重的方式，smallestSubarrays()用二分的方式时间复杂度会是 O(nlogn)
    */
    vector<int> smallestSubarrays_implementation3(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<pair<int, int>> ors; // (or值, 右端点坐标)，维护or值不重复，对于重复值右端点坐标取最小，这样子数组更短
        for (int i = n - 1; i >= 0; i--) {
            ors.push_back({0, i}); // ors越往右下标越小
            ors[0].first |= nums[i];

            // 这里相当于先push({0, i})，然后把ors中每个元素都 |= nums[i] 处理一遍，然后去重

            int k = 0; // k指向最后一个非重复元素
            // 每轮准备去重时，ors中最多O(logU)个不重复的元素，总时间复杂度O(nlogU)
            for (int j = 1; j < ors.size(); j++) { // LeetCode26. 删除有序数组中的重复项
                ors[j].first |= nums[i];
                if (ors[j].first == ors[k].first) {
                    ors[k].second = ors[j].second; // 取下标小的，这样子数组更短
                }
                else {
                    ors[++k] = ors[j];
                }
            }
            ors.resize(k + 1); // k指向最后一个非重复元素，一共k + 1个元素
            // 去重之后，ors[0]中的值单减无重复
            ans[i] = ors[0].second - i + 1; // ors一定非空，因为至少有[i, i]一个子数组
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2411 solu;
    auto a = solu.smallestSubarrays(*new vector<int>{1,0,2,1,3});
    auto b = solu.smallestSubarrays(*new vector<int>{8,10,8});

    auto c = solu.smallestSubarrays_implementation2(*new vector<int>{1,0,2,1,3});

    auto d = solu.smallestSubarrays_implementation3(*new vector<int>{1,0,2,1,3});
    return 0;
}
/*
url: https://leetcode.cn/problems/longest-nice-subarray/
相关: LeetCode3171. 找到按位与最接近 K 的子数组
标签: 【题单】滑动窗口与双指针, 位运算, logtrick, [special]
*/

// 本题的条件特殊，longestNiceSubarray_implementation2()非常特别，用[special]标记一下

#include <bits/stdc++.h>

using namespace std;

class Solution2401 {
public:
    /* 灵茶题解解法一，&结果为0，意味着2个int代表的集合相交为空，而1 <= nums[i] <= 10^9，不会为0，也就是说每个数至少
    都有一个1，以r为右端点，每次加一个数，要么和现有集合有交集，则循环停止，要么没有交集，那么现有集合就会多个1，总共只有logU
    个位置可以用来变1，所以虽然是二重循环，但是时间复杂度只是O(nlogU)，U为max(nums)。
    以r为右端点，左端点从r向左，|的结果会单增，且这个增长会维持原有的1不变，是1的位数的增长，只会有logU次，而不是普通的单增。

    LeetCode3171是算子数组可能得到的所有&值，这题是算互不相交能维持多长，有点不一样。
    */
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int ans = 1; // 长度为 1 的子数组始终视作优雅子数组
        for (int r = 0; r < n; r++) {
            // l从右往左，每步都要往至少一个位置上添1，由鸽笼原理，nums[l, r]的总交集保持为0会是困难的，很快就会出现一个笼子里有2只鸽子，只会有logU次循环
            int or_ = 0; // 用一个int代表总交集，or是c++关键字，不能直接写or
            int l = r;
            while (l >= 0 && (or_ & nums[l]) == 0) { // 交集为0时，可以继续向左增长
                or_ |= nums[l]; // 更新并集
                l--;
            }
            ans = max(ans, r - l);
        }
        return ans;
    }

    /* 灵茶题解解法二，
    对于新来的nums[r]，原本窗口互无交集，那么要和nums[r]也无交集，左端点l就会单调移动
    */
    int longestNiceSubarray_implementation2(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;
        int or_ = 0;
        for (int l = 0, r = 0; r < n; r++) {
            while ((or_ & nums[r]) != 0) {
                /* 通过异或去掉nums[l]，注意，列a, b的真值表，(a | b) ^ a = b不成立，例如(a, b) = (1, 1)。
                与，或并没有特别的逆运算可以从过程中把操作数消掉。
                但是这题特殊，在nums[r]加进来之前，窗口是优雅子数组，窗口数字之间是互不相交的，所以其1各在不同位置，
                这种特殊情况，把a异或进来是可以消掉a的。和a同为1的位置异或为了0，其它位置异或运算0是单位元，所以保持不变。非常特别！
                还有种理解方式：由于本题1互不重叠，所以or_加入元素时，用的|是等同于^的，也就是说，对于1互不重叠的数a,b,c，
                a | b | c ... = a ^ b ^ c ... ，而异或是有逆元的，a的异或逆元就是它本身，因为 a ^ a = 0(0是异或的单位元)，
                所以通过or_ ^= nums[l];，能把nums[l]消掉。即：a | b | c ^ a = a ^ b ^ c ^ a = b ^ c。
                参考: <https://leetcode.cn/problems/longest-nice-subarray/solutions/1799426/bao-li-mei-ju-pythonjavacgo-by-endlessch-z6t6/comments/2223577/>
                      <https://leetcode.cn/problems/longest-nice-subarray/solutions/1799426/bao-li-mei-ju-pythonjavacgo-by-endlessch-z6t6/comments/2404408/?parent=2223577>
                */
                or_ ^= nums[l];
                l++;
            }
            or_ |= nums[r]; // 这里改成or_ ^= nums[r]; 是一样的
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2401 solu;
    cout << solu.longestNiceSubarray(*new vector<int>{1,3,8,48,10}) << endl;
    cout << solu.longestNiceSubarray_implementation2(*new vector<int>{1,3,8,48,10}) << endl;
    return 0;
}
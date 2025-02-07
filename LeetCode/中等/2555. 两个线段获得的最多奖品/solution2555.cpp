/*
url: https://leetcode.cn/problems/maximize-win-from-two-segments/
参考: https://leetcode.cn/problems/maximize-win-from-two-segments/solutions/2093246/tong-xiang-shuang-zhi-zhen-ji-lu-di-yi-t-5hlh/
相关: LeetCode2271. 毯子覆盖的最多白色砖块数, LeetCode3413. 收集连续 K 个袋子可以获得的最多硬币数量
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2555 {
public:
    /* 我的做法，68 / 72 个通过的测试用例，但是不知道为什么错，待做: 为什么这样写不对？
    分两个区间相交和不相交来考虑，区间不相交时，是两个段，考虑第二个段，然后看前一个段能取到的最大值，
    区间相交时，是个区间最长2k的单滑窗，尽量包含多的位置，因此贪心地取长为2k，但是实际不需要特别考虑相交的情况。
    */
    int maximizeWin_wa(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        // 两个区间不相交，题意两个区间长度都必须为k。两个区间相交的情况一定更小，不用管，注意x轴无限长，不存在不得不相交的情况
        // 最优解一定可以满足区间右端点在coins某个位置上对齐，类似LeetCode2271. 毯子覆盖的最多白色砖块数
        int l2 = 0;
        int sum2 = 0;
        int sum1 = 0;
        int mx = 0;
        int l1 = 0, r1 = 0;
        int ans = 0;
        // 注意，最开始比如[l2, r2]在[0, 0]处时，不代表不满足题目要求的区间 r - l == k，此时l2相当于在负数位置，所以刚开始时长度不够k的问题不必太在意
        for (int r2 = 0; r2 < n; r2++) {
            // 即便prizePositions有重复元素，比如3 3 3，现在没到最右边那个3不要紧，后面会到
            sum2++;
            while (prizePositions[l2] < prizePositions[r2] - k) {
                sum2--;
                l2++;
            }
            while (r1 < l2) {
                sum1++;
                while (prizePositions[l1] < prizePositions[r1] - k) {
                    sum1--;
                    l1++;
                }
                mx = max(mx, sum1);
                ans = max(ans, sum2 + mx);
                r1++;
            }
        }
        return ans;
    }

    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        int l = 0;
        int ans = 0;
        vector<int> mx(n + 1); // 向右偏移1防出现-1
        for (int r = 0; r < n; r++) {
            while (prizePositions[l] < prizePositions[r] - k) {
                l++;
            }
            ans = max(ans, mx[l - 1 + 1] + r - l + 1);
            mx[r + 1] = max(mx[r], r - l + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2555 solu;
    cout << solu.maximizeWin(*new vector<int>{1,1,2,2,3,3,5}, 2) << endl;
    return 0;
}
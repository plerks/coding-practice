/*
url: https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/description/
参考: https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/solutions/1202043/zui-shao-jiao-huan-ci-shu-lai-zu-he-suo-iaghf/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2134 {
public:
    /* 把1移到一起就是把1中间的0都换出来，所以移动次数就是中间0的个数。
    注意把0111变成1110只需一次操作而非三次，是交换而非依次推动
    */
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0; // nums中1的个数
        for (int x : nums) cnt += x;
        if (cnt == 0) return 0;
        int left = 0;
        int right = cnt - 1; // 初始窗口
        int t = 0;
        // 但是这时先不把right加进去
        for (int i = left; i < right; i++) {
            t += (nums[i] == 0);
        }
        int ans = INT_MAX;
        // 每次循环，先把right加入，再移动左，这样就是每次操作就是接上的
        while (left < n) {
            t += (nums[right % n] == 0);
            ans = min(ans, t);
            t -= ((nums[left] == 0));
            left++;
            right++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2134 solu;
    cout << solu.minSwaps(*new vector<int>{0,1,1,1,0,0,1,1,0}) << endl;
    cout << solu.minSwaps(*new vector<int>{0,0,0}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/find-the-longest-equal-subarray/description/
参考: https://leetcode.cn/problems/find-the-longest-equal-subarray/solutions/2396401/fen-zu-shuang-zhi-zhen-pythonjavacgo-by-lqqau/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2831 {
public:
    /* 参考灵茶题解，
    考虑要什么数连起来，考虑x作为右边界，是否有单调性？
    有，如果[l,x]不能在k步内删干净其它数，则[l-1,x]也一定不能，有单调性，所以能用滑窗在O(n)内解决。
    如何知道有多少个其它数？
    把x的标号记录下来，[l, r]知道区间长度，标号数组的长度知道有多少个x，这样就能知道要删多少步
    */
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        int ans = 0;
        // 滑窗
        for (auto &[x, pos] : mp) {
            int sz = pos.size();
            int l = 0;
            for (int r = 0; r < sz; r++) {
                // 把pos[l], pos[r]之间的其它数删光，需要 (pos[r]-pos[l]+1) - (r-l+1)次操作
                while ((pos[r] - pos[l] + 1) - (r - l + 1) > k) l++;
                ans = max(ans, r - l + 1);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2831 solu;
    cout << solu.longestEqualSubarray(*new vector<int>{1,3,2,3,1,3}, 3) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/bag-of-tokens/
标签: 【题单】滑动窗口与双指针, 贪心
*/
#include <bits/stdc++.h>

using namespace std;

class Solution948 {
public:
    // 我的解法，时间复杂度O(nlogn)
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size();
        sort(tokens.begin(), tokens.end());
        // 每次拿分/拿能量，最大化分，所以用tokens的小值换分，再用分拿大的能量，这样是净赚能量，分不变
        // 要在某个时机选择不断用能量换分
        int l = 0, r = n - 1;
        int ans = 0;
        vector<int> pre(n + 1);
        partial_sum(tokens.begin(), tokens.end(), pre.begin() + 1);
        while (l < r) {
            // 假设以当前power无限换分，能换多少个？
            // 找最后一个sum[l, r] <= power的位置r，即最后一个pre[r] - pre[l - 1] <= power的位置
            int last = upper_bound(pre.begin(), pre.end(), power + pre[l]) - pre.begin() - 1 - 1; // 要额外减1才是在tokens中的位置
            ans = max(ans, last - l + 1);
            if (power < tokens[l]) break;
            power += tokens[r--] - tokens[l++];
        }
        if (l == r && power >= tokens[l]) ans = max(1, ans);
        return ans;
    }

    // 官方题解解法，分是万能的，不管右边是多少，换能量都只消耗1分，从左边贪婪地拿分，直到power不够才去右边换能量，然后继续在左边贪婪拿分。时间复杂度O(nlogn)
    // 写法参考官方题解评论区的一份代码，这样写不需要用一个变量记录中间过程中出现的最大值，直接在ans上操作就行
    int bagOfTokensScore_implementation2(vector<int>& tokens, int power) {
        int n = tokens.size();
        sort(tokens.begin(), tokens.end());
        int l = 0, r = n - 1;
        int ans = 0;
        while (l <= r) {
            if (power < tokens[l]) break;
            while (l <= r && power >= tokens[l]) { // 贪心换分
                ans++;
                power -= tokens[l++];
            }
            if (r - l + 1 >= 2 && ans > 0) { // 用分去右边换能量时要保证区间至少还有2个元素，这样右左各一下，ans不减，否则最后剩一个元素时可能用分换了溢出无用的能量
                ans--;
                power += tokens[r--];
            }
        }
        return ans;
    }

    /* 官方题解评论区代码的原写法<https://leetcode.cn/problems/bag-of-tokens/solutions/15987/ling-pai-fang-zhi-by-leetcode/comments/2333032/>，
    枚举步数，最多n步操作，每次循环只操作一次l或者r或者退出循环，当i < n - 1时就代表区间长度>=2。
    */
    int bagOfTokensScore_implementation3(vector<int>& tokens, int power) {
        int n = tokens.size();
        sort(tokens.begin(), tokens.end());
        int l = 0, r = n - 1;
        int ans = 0;
        for (int i = 0; i < n; i++) { // 枚举步数
            if (power >= tokens[l]) {
                ans++;
                power -= tokens[l];
                l++;
            }
            else if (ans > 0 && i < n - 1) { // i < n - 1代表区间至少还有2个元素，这样右左各一下，ans不减，否则最后剩一个元素时可能用分换了溢出无用的能量
                ans--;
                power += tokens[r];
                r--;
            }
            else break; // 换不了分，也换不了能量
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution948 solu;
    // cout << solu.bagOfTokensScore(*new vector<int>{200,100}, 150) << endl;
    // cout << solu.bagOfTokensScore(*new vector<int>{100,200,300,400}, 200) << endl;
    // cout << solu.bagOfTokensScore(*new vector<int>{81,91,31}, 73) << endl;
    // cout << solu.bagOfTokensScore(*new vector<int>{71,55,82}, 54) << endl;

    cout << solu.bagOfTokensScore_implementation2(*new vector<int>{100,200,300,400}, 200) << endl;
    return 0;
}
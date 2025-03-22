/*
url: https://leetcode.cn/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
标签: 【题单】滑动窗口与双指针, 贡献法
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int maxn = 1e5 + 1;
int p[maxn + 1]; // p[i]表示2^i % MOD，不能用pow，因为include <bits/stdc++.h>后有pow这个函数，会重定义

// 参考官方题解，若用fastPow一个个调用，单个时间复杂度O(logi)，总时间复杂度可能达到O(nlogn)，不如直接预处理全部，总时间O(n)
auto init = []() {
    p[0] = 1;
    for (int i = 1; i <= maxn; i++) {
        p[i] = p[i - 1] * 2 % MOD;
    }
    return 0;
}();

class Solution1498 {
public:
    // 我的解法，这里l可能越过r要处理，当t == r时是1 + 1 + 2 + 4 + ...，要排除第一个1才是等比数列要特判，r == 0要特判
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        long long ans = 0;
        sort(nums.begin(), nums.end());
        int l = 0;
        for (int r = n - 1; r >= 0; r--) {
            while (l <= r && nums[l] + nums[r] <= target) l++;
            /* 左端点在[0, l-1]，但是l - 1可能越过r，所以左端点最右在 t = min(r, l - 1)，
            这题是子序列，
            假设选t为左端点，中间[t, r)任选
            假设选l-1为左端点，中间[t - 1, r)任选
            ...
            假设选0为左端点，中间[1, r)任选
            但是当t == r和t == r - 1时，中间的元素个数都是0，得特判
            
            若t == r，则数量为1,
            若t == r - 1，则数量为1，
            若t == r - 2，则数量为2，
            ...
            除去最开始可能出现的1，剩下部分是2^(r - t - 1) + ... + 2^(r - 1) = 2^r - 2^(r-t-1)，r为0时又要特判，不然r - 1是负数
            */
            int t = min(r, l - 1); // 左端点最多在r处，不能更右
            if (r == 0) {
                if (t == 0) ans += 1;
                break;
            }
            if (t == r) {
                ans += 1;
                t--;
            }
            ans = (ans + fastPow(2, r) - fastPow(2, r - t - 1) + MOD) % MOD;
            /* for (int i = r - t - 1; i <= r - 1; i++) {
                ans += 1 << i;
            } */
        }
        return ans;
    }

    /* 官方题解解法，贡献法，
    固定一个端点，算剩余部分的贡献，写出来不用处理各种特殊情况
    */
    int numSubseq_implementation2(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // 固定左端点，看右侧范围
        int r = n - 1;
        long long ans = 0;
        for (int l = 0; l < n; l++) {
            if (l > r) break; // 相向双指针，这里合法区间是[l, r]，越过时则不用再计算了。不过这行不要也行，后面需要判断if (l <= r)
            // 这里枚举的是左端点，l > r时代表合法区间长为0，所以可以直接break;
            // 而numSubseq()枚举的是右端点，l > r时代表合法部分很大，不能直接break;
            // 由于题目要求的是和<=target，所以这里第一层枚举左端点/枚举右端点是不一样的
            while (l <= r && nums[l] + nums[r] > target) r--;
            // [l, r]满足min + max <= target，l要固定，则所有子序列的总数为2^(r - l)
            if (l <= r) ans = (ans + p[r - l]) % MOD;
        }
        return ans;
    }

    /* 官方题解评论区的写法<https://leetcode.cn/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/solutions/310424/man-zu-tiao-jian-de-zi-xu-lie-shu-mu-by-leetcode-s/comments/2404549/>，
    单步单步地来，用while(l <= r)来控制双指针，并且每次循环只走一步，这样每次计算前都判断了l <= r
    */
    int numSubseq_implementation3(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long ans = 0;
        int l = 0, r = n - 1;
        while (l <= r) {
            if (nums[l] + nums[r] > target) r--;
            else {
                ans = (ans + p[r - l]) % MOD;
                l++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1498 solu;
    // cout << solu.numSubseq(*new vector<int>{3,5,6,7}, 9) << endl;
    // cout << solu.numSubseq(*new vector<int>{3,3,6,8}, 10) << endl;
    cout << solu.numSubseq(*new vector<int>{2,3,3,4,6,7}, 12) << endl;

    cout << solu.numSubseq_implementation2(*new vector<int>{3,5,6,7}, 9) << endl;
    cout << solu.numSubseq_implementation2(*new vector<int>{2,3,3,4,6,7}, 12) << endl;
    return 0;
}
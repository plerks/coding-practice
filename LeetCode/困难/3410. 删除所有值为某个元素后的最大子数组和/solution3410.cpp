/*
url: https://leetcode.cn/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/
参考: https://leetcode.cn/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/solutions/3039428/liang-chong-fang-fa-xian-duan-shu-qian-h-961z/
      https://www.bilibili.com/video/BV1SzrAYMESJ/
相关: LeetCode53. 最大子数组和
标签: LeetCode第147场双周赛, 线段树, 前后缀分解
*/

// 这次双周赛2题

#include <bits/stdc++.h>

using namespace std;

// 单点更新 + 查询区间ans的线段树
struct SegTree {
    struct Info {
        long long ans, sum, pre, suf;
    };

    vector<Info> tree;

    SegTree(vector<int>& nums) {
        int n = nums.size();
        tree.resize(2 << (32 - __builtin_clz(n)));
        build(nums, 0, n - 1, 1);
    }

    void build(vector<int>& nums, int s, int t, int p) {
        if (s == t) {
            // 注意叶节点没有和0取max，所以维护的是非空子数组，但后面改值为0当作删除，线段数维护非空子数组和题目要求的删除值之后非空子数组有区别
            tree[p] = {nums[s], nums[s], nums[s], nums[s]};
            return;
        }
        int m = (s + t) / 2;
        build(nums, s, m, p * 2);
        build(nums, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    // 单点更新
    void update(int I, int val, int s, int t, int p) {
        if (I < s || I > t) return;
        if (s == t) {
            tree[p] = {val, val, val, val};
            return;
        }
        int m = (s + t) / 2;
        update(I, val, s, m, p * 2);
        update(I, val, m + 1, t, p * 2 + 1);
        pushup(p);
    }

    void pushup(int p) {
        Info& a = tree[p * 2];
        Info& b = tree[p * 2 + 1];
        tree[p] = {
            max({a.ans, b.ans, a.suf + b.pre}),
            a.sum + b.sum,
            max(a.pre, a.sum + b.pre),
            max(b.suf, b.sum + a.suf)
        };
    }
};

class Solution3410 {
public:
    /* 灵茶山艾府题解解法一，线段树
    LeetCode53中的分治写法
    为了求某个区间[l, r]的最大子数组和ans，分治考虑，
    若不跨中点，则为左右子区间的最大子数组和取大，
    若跨中点，则为 左子区间从右端点往左的最大子数组suf + 右子区间从左端点往右的最大子数组pre，二者取最大。
    为了求pre和suf，同样需要分治，以suf为例，若需要跨中点，则是右子区间的总和sum + 左子区间的suf，若不需要，为右子区间的suf，二者取最大。

    因此，每个区间需要维护4个变量{ans, sum, pre, suf}

    有了线段树之后，就可以在单点更新后快速查询值，暴力枚举删除的情况，把每个值变成0即等价于删除值，时间复杂度O(nlogn)
    */
    long long maxSubarraySum(vector<int>& nums) {
        int n = nums.size();
        SegTree st(nums);
        long long ans = st.tree[1].ans; // 不删数的情况
        // 题目要求子数组非空，若子数组有正数，则后面通过st求出的最大子数组一定非空，而子数组全<=0等价于一开始st.tree[1].ans <= 0
        if (ans <= 0) return ans;
        unordered_map<int, vector<int>> pos; // 每个值的出现位置
        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) pos[nums[i]].push_back(i); // 删正数/0一定不会得到最大
        }
        for (auto& [x, idx] : pos) {
            for (int p : idx) {
                st.update(p, 0, 0, n - 1, 1);
            }
            ans = max(ans, st.tree[1].ans);
            // 恢复
            for (int p : idx) {
                st.update(p, x, 0, n - 1, 1);
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二，前后缀分解
    用pre[i]表示从i位置往前，把 x=nums[i] 全部删除(变成0)后的最大非空子数组和(需要包括i - 1这个位置)，
    用suf[i]表示从i位置往后，把 x=nums[i] 全部删除(变成0)后的最大非空子数组和(需要包括i + 1这个位置)，
    只要算出这两个，就可以计算出答案。
    以pre[i]为例，如何计算？
    考虑左边上一次x出现的位置，若实际的最大子数组越过了这个位置，则为pre[last[x]] + sum[last[x] + 1 ... x - 1]
    若实际的最大子数组未越过这个位置，则为[last[x] + 1, x - 1]内的最大子数组和，这带个last[x]边界限制，很难处理，怎么办？
    实际上可以不考虑有左边界的限制，只需考虑[0, x - 1]内的非空最大子数组和(记为f)即可，下面说明即使f对应的数组越过了last[x]，也不会有问题
    若 x <= 0，则 pre[last[x]] + sum[last[x] + 1 ... x - 1] 一定会更大(少个负数x)，不会影响pre[i]的值
    若 x > 0，我们求出的 f 可能不合法地变大了，例如 1 2 1，到 i == 2时，pre[2]为3，但是实际1也要被删除，pre[2]不合法地大了
    但是，由于x为正，wrong_pre[i] + x能得到更大的子数组和，而这种情况会被考虑到(删除其它数时，或者一个数都不删时)，所以最终答案不会有问题。

    为了计算pre[last[x]] + sum[last[x] + 1 ... x - 1]，需要前缀和，但是可以简化，
    原式 = pre[last[x]] + prefixSum(x - 1) - prefixSum(last[x])
    直接用一个变量s记录当前前缀和，并把pre[last[x]] - prefixSum[last[x]]存到map中

    时间复杂度O(n)
    */
    long long maxSubarraySum_implementation2(vector<int>& nums) {
        int n = nums.size();
        // 此题要求子数组非空，初值要设为 LLONG_MIN / 2 这样的数而不是0，在选了数前要是负无穷，这样一旦选了数就把决定权交给它
        vector<long long> pre(n);
        unordered_map<int, long long> last; // last不用记录位置，直接记录pre[last[x]] - prefixSum[last[x]]
        long long f = LLONG_MIN / 2; // 最大子数组和
        long long s = 0; // 前缀和
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            pre[i] = f;
            if (last.count(x)) {
                pre[i] = max(pre[i], last[x] + s); // 现在s还没加上nums[i]
            }
            if (f < 0) f = 0; // 丢掉之前的，下一步马上要加nums[i]，所以不用担心f为空子数组
            f += x;
            s += x;
            last[x] = pre[i] - s;
        }

        vector<long long> suf(n);
        last.clear();
        f = LLONG_MIN / 2;
        s = 0;
        for (int i = n - 1; i >= 0; i--) {
            int x = nums[i];
            suf[i] = f;
            if (last.count(x)) {
                suf[i] = max(suf[i], last[x] + s);
            }
            if (f < 0) f = 0;
            f += x;
            s += x;
            last[x] = suf[i] - s;
        }

        long long ans = accumulate(nums.begin(), nums.end(), 0LL); // 什么都不删的情况
        for (int i = 0; i < n; i++) {
            ans = max({ans, pre[i] + suf[i], pre[i], suf[i]});
        }
        return ans;
    }

    /* 灵茶山艾府题解解法三，但是按我的理解来写的，和原本写法有些出入

    考虑最优区间右边界在j处，现在需要考虑左边界在何处以及删除的数应该是谁，
    记左边界为i，删除的数为x，则子数组和为 s[j] - s[i - 1] - kx，k为[i, j]中x的个数，s为前缀和。
    于是需要求的是i, x使得s[i - 1] + kx最小，实际并不需要枚举i和x，

    s[i - 1]和kx分别代表对nums[0...j]删除一个前缀，然后剩下部分再选一个数删除

    若x取nums[j]，若x不是第一次出现，则相比之前的 s[i_{nums[j]} - 1] + k * nums[j] ，再多删一个nums[j]能最小
                 若x是第一次出现，则删最小的前缀，再删这个第一次出现的nums[j]能最小

    若x不取nums[j]，则就是之前得到的 min{s[i - 1] + kx}，若之前的 min{s[i - 1] + kx} 对应的x取值就是nums[j]，
    则之前的min{s[i - 1] + kx}的值我们漏掉了一个该删的nums[j]，但这就是第一种情况，不会有错

    若[i, j]选择不删除数，则 s[i - 1] + kx 的最小值就是s[i - 1]最小值，实际不用单独考虑这种情况，合并到x不取nums[j]的情况里了

    题目要求子数组非空，但是x取nums[j]时，有可能把子数组删空，这种情况说明[0, j]全是负数，若这种情况成为了最终的ans，则说明整个nums
    全为负数，则在开头特判一下:
        int mx = *max_element(nums.begin(), nums.end());
        if (mx <= 0) return mx;
    灵茶山艾府的代码里是: 直接就先把s加上了nums[j]，保证至少有一个数，这样的风险是，对于nums = {2,-2,2,-2}，
    可能产生{2,2,-2}这样的子数组(删但是没删干净)，
    若nums[j] > 0，则一定是不删除j的情况下子数组和更大，最终ans不会有问题
    若nums[j] < 0，则取出的序列要么就是单个nums[j]，要么至少一个正数，则在前面那个正数的位置已经获得了更大的ans，最终ans不会有问题
    */
    long long maxSubarraySum_implementation3(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        if (mx <= 0) return mx;
        unordered_map<int, long long> map;
        long long all_min = 0; // s[i - 1] + kx能取到的最小值，k==0或者[i, j]的x的数量
        long long ans = INT_MIN;
        long long s = 0;
        long long min_s = 0; // s[0 ... i - 1]的最小值
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            /* 删nums[j]能获得的最小，若num为正则不该删除num，该删除某个前缀 + 某个特定值x/不删值，但这种情况包含在了all_min的旧值里，
            一开始all_min就包含了删除某个前缀 + 不删值的情况(初值0)，不删num也就是j-1时删除某个前缀 + 某个特定值x/不删值。
            */
            map[num] = min(map[num], min_s) + num;
            all_min = min(all_min, map[num]);
            s += num;
            ans = max(ans, s - all_min);
            min_s = min(min_s, s);
        }
        return ans;
    }

    // 灵茶山艾府题解解法三原本的写法
    long long maxSubarraySum_implementation4(vector<int>& nums) {
        unordered_map<int, long long> map;
        long long all_min = 0;
        long long ans = INT_MIN;
        long long s = 0;
        long long non_del_min_s = 0; // s[0 ... i - 1]的最小值，注意这时是没把删除数的那次机会用掉的
        for (int x : nums) {
            s += x;
            ans = max(ans, s - all_min);
            if (x < 0) { // 如果 x < 0，有删除数的机会的话是应该删除x的
                map[x] = min(map[x], non_del_min_s) + x; // 要么顺着之前删x的情况继续删x，要么用之前没删除过数的机会删除x
                all_min = min(all_min, map[x]);
                non_del_min_s = min(non_del_min_s, s);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3410 solu;

    cout << solu.maxSubarraySum(*new vector<int>{-3,2,-2,-1,3,-2,3}) << endl;
    cout << solu.maxSubarraySum(*new vector<int>{-2,-2,-2}) << endl;

    cout << solu.maxSubarraySum_implementation2(*new vector<int>{-3,2,-2,-1,3,-2,3}) << endl;
    cout << solu.maxSubarraySum_implementation2(*new vector<int>{-2,-2,-2}) << endl;

    cout << solu.maxSubarraySum_implementation3(*new vector<int>{-3,2,-2,-1,3,-2,3}) << endl;
    cout << solu.maxSubarraySum_implementation3(*new vector<int>{-2,-2,-2}) << endl;

    cout << solu.maxSubarraySum_implementation4(*new vector<int>{-3,2,-2,-1,3,-2,3}) << endl;
    cout << solu.maxSubarraySum_implementation4(*new vector<int>{-2,-2,-2}) << endl;
    return 0;
}
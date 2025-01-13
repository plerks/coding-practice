/*
url: https://leetcode.cn/problems/count-non-decreasing-subarrays-after-k-operations/description/
参考: https://www.bilibili.com/video/BV1HKcue9ETm/
      https://leetcode.cn/problems/count-non-decreasing-subarrays-after-k-operations/solutions/3045053/on-xian-xing-zuo-fa-dan-diao-zhan-di-qia-ay5b/
      https://leetcode.cn/problems/count-non-decreasing-subarrays-after-k-operations/solutions/3045049/shuang-zhi-zhen-dan-diao-zhan-dan-diao-d-hmt6/
相关: LeetCode239. 滑动窗口最大值
标签: LeetCode第432场周赛, 滑动窗口
*/

// 这次周赛2题

#include <bits/stdc++.h>

using namespace std;

class Solution3420 {
public:
    /* 灵茶山艾府题解解法一
    多加一个数，需要变成单增的操作次数会不变或变多，子数组越长越不满足要求，有单调性，考虑滑窗。
    从左到右滑窗，右边新加一个数，只需把这个数变成前面的最大值，由于左侧还涉及到删除数，这里要用单调队列维护窗口最大值
    左边出去一个数改怎么处理？
    以[6, 3, 1, 2, 4, 4]为例，
    最开始，为了单增，需要变成[6, 6, 6, 6, 6, 6]，
    6出去后，数组变为[3, 1, 2, 4, 4]，这时数组应该怎么变？
    以单增的点分块，每个数需要变成其左边那个大的数，[3, 1, 2, 4, 4]应该变为[3, 3, 3, 4, 4]，
    但是不是每个数往左看自己该变成谁，例如[3, 2, 1]应该变为[3, 3, 3]而非[3, 2, 2]，
    而是每个数往右看自己该改变哪些数，[3, 2, 1, 4, 4]，3会把2, 1都变成3，直到到4。

    对nums中每个数x，我们需要知道所有y: y的左侧第一个比y大的元素为x
    删除x后，这些数会作为新的端的起点，如何知道段的长度？记录y右侧第一个比y大的元素的位置。
    这两个都可以通过单调栈完成。
    */
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> g(n); // g[i]中存的是所有以nums[i]为左边第一个更大数的元素(的下标)，相当于是个树形结构
        stack<int> st;
        vector<int> pos_r(n, n); // pos_r[i]为nums[i]右侧第一个比nums[i]大的元素的下标
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (!st.empty() && nums[st.top()] <= x) {
                pos_r[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) {
                g[st.top()].push_back(i);
            }
            st.push(i);
        }
        
        long long ans = 0;
        int cnt = 0; // 当前调为单增需要的操作次数
        int l = 0;
        deque<int> q; // LeetCode239. 滑动窗口最大值，单调队列求窗口最大值

        // 滑窗
        for (int r = 0; r < n; r++) {
            int x = nums[r];
            // 加入r
            while (!q.empty() && nums[q.back()] <= x) {
                q.pop_back();
            }
            q.push_back(r);
            // 加入x后，变为单增需要的操作次数
            cnt += nums[q.front()] - x;

            // 滑动左边使得cnt <= k
            while (cnt > k) {
                int out = nums[l];
                // 删除l
                for (int i : g[l]) { // g可以看作一棵树，现在g的各个儿子会引领一段，而之前它们都要变成out
                    if (i > r) break;
                    cnt -= (out - nums[i]) * (min(pos_r[i], r + 1) - i);
                }
                l++;

                // 单调队列的维护
                if (q.front() < l) q.pop_front();
            }
            ans += r - l + 1; // 子数组可以取[l, r]到[r, r]，共r - l + 1种情况
        }
        /* 虽然代码有三重循环，但是有前两层是滑窗，时间复杂度O(n)；for (int i : g[l])这层循环，
        每个元素左侧第一个比它大的元素最多只有一个，所以g中的元素的总个数为O(n)，每个元素露头引领一次，所以for (int i : g[l])
        的总时间是O(n)。综上，虽然有三重循环，但时间复杂度是O(n)，很奇妙。
        */
        return ans;
    }

    /* 灵茶山艾府题解解法二
    从右往左滑(枚举左端点，右端点在内层循环更新)，左侧增加节点计算方式与之前左侧删除节点类似，但要维护窗口中元素的树形结构
    右侧删除节点r时，原本r的值是r的父节点的值，操作次数是p - nums[r]，现在不需操作了，操作次数减少p - nums[r]。
    这里子树的维护与合并很精妙，合并时子树只需把规模累加给父节点即可，其本身结构可以丢弃了。
    */
    long long countNonDecreasingSubarrays_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long cnt = 0;
        deque<pair<int, int>> q; // (子树根节点的值, 树的规模)
        // q从左到右放了各棵合并过后的子树
        int r = n - 1;
        for (int l = n - 1; l >= 0; l--) {
            int x = nums[l];
            int size = 1; // 现在只有一个x
            while (!q.empty() && q.front().first <= x) {
                auto [v, sz] = q.front();
                q.pop_front();
                size += sz;
                cnt += (long long)(x - v) * sz;
                /* 左侧新加入的节点x不断地从左往右合并比x小的树，把他们都变成x，
                后面x会遮挡住这些子树，他们会跟着x变，所以它们直接出栈，并只把节点个数计数到x里就行
                */
            }
            q.push_front({x, size});
            
            // 滑动右边使得cnt <= k
            while (cnt > k) {
                auto& [v, sz] = q.back(); // 最右边的树，注意这里是引用
                cnt -= v - nums[r];
                r--;
                sz--; // 子树规模-1
                if (sz == 0) q.pop_back();
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3420 solu;
    cout << solu.countNonDecreasingSubarrays(*new vector<int>{6,3,1,2,4,4}, 7) << endl;
    cout << solu.countNonDecreasingSubarrays_implementation2(*new vector<int>{6,3,1,2,4,4}, 7) << endl;
    return 0;
}
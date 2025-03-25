/*
url: https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/description/
LeetCode参考: https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/solutions/1658410/by-endlesscheng-j6pp/
              https://www.bilibili.com/video/BV1Le4y1R7xu/
相关: LeetCode3161. 物块放置查询, LeetCode795. 区间子数组个数
标签: 并查集, 并查集的奇妙用法, [special]
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2334 {
public:
    /* 灵茶山艾府题解解法一。之前看到这个解法的时候还没学并查集，没看懂是什么意思，就用的单调栈的解法做的，
    但是看评论说这里并查集的使用方式很特别，就一直记着这个。
    LeetCode3161. 物块放置查询中又遇到了并查集的特殊用法，就再回来看看这个，这里这个并查集的用法比
    LeetCode3161. 物块放置查询的还特别，甚至可以说挺怪。
    LeetCode795. 区间子数组个数也可以用这种并查集思路。
    */
    int validSubarraySize(vector<int>& nums, int threshold) {
        /* 考虑子数组中的最小值，其应该越大越好，长度应该越长越好。于是考虑从大到小遍历nums，现在考虑nums[id]
        为子数组最小值，其能扩展多长？
        */
        int n = nums.size();
        vector<int> parent(n + 1); // 最后必须得有个哨兵
        iota(parent.begin(), parent.end(), 0);
        vector<int> size(n + 1, 1);
        vector<int> idx(n); // 标号数组
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) {
            return nums[x] > nums[y];
        });

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        for (int id : idx) {
            // 现在考虑子数组以nums[id]为最小值，要让子数组尽量长

            // 只往右扩展，不会出错误，具体原因写在了后面。

            /* 这里合并的逻辑非常怪，不管id + 1位置是否在前面已经访问过，都把id合并到id + 1所属的分量里，这会导致分量的最右一个
            位置是个还没被访问过的，<= 当前已访问过的最小值的值 (以下称为未访问小值，不再特别强调可能相等)。同时，这也意味着parent
            最右边必须加一个哨兵，不然维护不了这个性质。可以认为从id找到的分量(记长度为n)，要当成左闭右开区间来解释[0, n-1)
            */

            /* 如果id + 1位置是前面已经访问过了的元素，则其一定比nums[id]大，以nums[id]为最小值，子数组可以扩展id + 1所在的分量，
            将id与id + 1合并。如前所述，虽然id + 1的分量中大部分都是已访问过的，>= nums[id]的值，但是最右边一个位置挂着一个
            未访问小值。合并之后从id找到的分量最右边挂着一个未访问小值。
            */

            /* 如果id + 1位置是前面还未访问的元素，则其一定<=nums[id]，则其一定自成一个分量，也将id合并到id + 1。合并之后从id
            找到的分量最右边挂着一个未访问小值。
            */

            /* 这里只往右边合并，对于以nums[id]为最小值的子数组进行最大扩展，只扩展了右边，如果id左边相邻位置还有和nums[id]相等
            的元素nums[x]，会不会导致错误？
            不会，若x已被访问过，则其要么已经将自己加入到了id的size里，要么(x, id)中间隔着小于nums[id]的值，以nums[id]为最小值
            本来就无法向左扩展到x；
            若x还未被访问，则在之后访问x时会考虑到这个最小值为nums[x](==nums[id])，且更长，更容易满足要求的子数组。

            到了要访问未访问小值时怎么办？
            无所谓，枚举nums[id]为子数组最小值并向右扩展时，不会把小值包含进来，只要保证这一点就够了。轮到未访问小值当nums[id]时也一样。

            这里并查集分量的根是最右边那个未访问小值。
            */
            int j = find(id + 1);
            parent[id] = j; // 什么都不管，直接把id合并到j里
            size[j] += size[id];
            // 注意从id找到的连通分量最右边挂着一个未访问小值，右边是开的，要去掉最右边一个
            if (nums[id] > threshold / (size[j] - 1)) return (size[j] - 1);
        }
        return -1;
    }

    /* 换一种思路，让已访问的元素尽量合并，由于是从大到小访问的，效果就是大的元素尽量合并了，好理解很多。这样使用并查集就和
    LeetCode3161. 物块放置查询中的并查集使用方式很像了。 */
    int validSubarraySize_implementation2(vector<int>& nums, int threshold) {
        int n = nums.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        vector<int> size(n, 1);
        vector<int> idx(n); // 标号数组
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) {
            return nums[x] > nums[y];
        });

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        auto unite = [&](int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry) return;
            // 这里不考虑分量大小，直接写成把y所在的分量合并到x所在的分量
            parent[ry] = rx;
            size[rx] += size[ry];
        };

        // 让已访问的元素尽量合并，由于是从大到小访问的，效果就是大的元素尽量合并了
        for (int id : idx) {
            if (id + 1 < n && nums[id] <= nums[id + 1]) { // nums[id] <= nums[id + 1]，则nums[id]就仍然为最小值
                unite(id, id + 1);
            }
            if (id - 1 >= 0 && nums[id] <= nums[id - 1]) {
                unite(id, id - 1);
            }
            if (nums[id] > threshold / size[find(id)]) return size[find(id)];
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2334 solu;
    vector<int> nums = {1,3,4,3,1};
    cout << solu.validSubarraySize(nums, 6) << endl;
    cout << solu.validSubarraySize_implementation2(nums, 6) << endl;
    return 0;
}

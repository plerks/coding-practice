/*
url: https://leetcode.cn/problems/count-special-subsequences/description/
参考: https://leetcode.cn/problems/count-special-subsequences/solutions/3033284/shi-zi-bian-xing-qian-hou-zhui-fen-jie-p-ts6n/
相关: LeetCode1512. 好数对的数目
标签: LeetCode第430场周赛, 动态维护
*/

#include <bits/stdc++.h>

using namespace std;

// 对pair hash，得命名成pair_hash，命名成hash会有歧义，有std::hash。最后必须写这个const，不然编译不通过
struct pair_hash {
    int operator()(const pair<int, int>& p) const {
        return p.first * 1001 + p.second;
    }
};

class Solution3404 {
public:
    /* 周赛时是这样想的，首先共有n^2个pair，把每个(p, r), (q, s)的乘积先算出来，放到map里，然后需要判断 p < q < r < s，
    由于pair是按(p, r), (q, s)存放的，所以判断这个大小关系时是错位的，就肯定会超时。
    后面才想到把 nums[p] * nums[r] == nums[q] * nums[s] 转化成 nums[p] / nums[q] == nums[s] / nums[r]，
    这样只需判断左右关系即可，需要用2个map存商，然后用除gcd的方式换成同一形式以判等，对每个(p, q)，二分查找以确定符合的(r, s)的个数。
    最后时间复杂度O(n^2 * logn)。
    不过时间来不及写了，周赛结束过了15分钟才写出来。
    执行用时2640ms
    */
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();
        map<pair<int, int>, vector<pair<int, int>>> map1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j < n; j++) {
                int x = nums[i];
                int y = nums[j];
                map1[{x / __gcd(x, y), y / __gcd(x, y)}].push_back({i, j});
            }
        }
        map<pair<int, int>, vector<pair<int, int>>> map2;
        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j < n; j++) {
                int x = nums[i];
                int y = nums[j];
                map2[{y / __gcd(x, y), x / __gcd(x, y)}].push_back({i, j});
            }
        }
        long long ans = 0;
        for (auto& pair : map1) {
            auto& vec1 = pair.second;
            auto& vec2 = map2[pair.first];
            sort(vec2.begin(), vec2.end());
            for (int i = 0; i < vec1.size(); i++) {
                int p = vec1[i].first;
                int q = vec1[i].second;
                auto it = upper_bound(vec2.begin(), vec2.end(), make_pair(q + 1, INT_MAX));
                int index = it - vec2.begin();
                ans += vec2.size() - index;
            }
        }
        return ans;
    }

    // 换成用unordered_map，执行用时2075ms
    long long numberOfSubsequences_implementation2(vector<int>& nums) {
        int n = nums.size();
        unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> map1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j < n; j++) {
                int x = nums[i];
                int y = nums[j];
                map1[{x / __gcd(x, y), y / __gcd(x, y)}].push_back({i, j});
            }
        }
        unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> map2;
        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j < n; j++) {
                int x = nums[i];
                int y = nums[j];
                map2[{y / __gcd(x, y), x / __gcd(x, y)}].push_back({i, j});
            }
        }
        long long ans = 0;
        for (auto& pair : map1) {
            auto& vec1 = pair.second;
            auto& vec2 = map2[pair.first];
            sort(vec2.begin(), vec2.end());
            for (int i = 0; i < vec1.size(); i++) {
                int p = vec1[i].first;
                int q = vec1[i].second;
                auto it = upper_bound(vec2.begin(), vec2.end(), make_pair(q + 1, INT_MAX));
                int index = it - vec2.begin();
                ans += vec2.size() - index;
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法一，
    前后缀分解，枚举 p q 的可能性的同时，记录后面 r s 的商的个数，并在 q 向右移动时撤销一个不再合法的 r。
    执行用时811ms。
    */
    long long numberOfSubsequences_implementation3(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> map;
        long long ans = 0;
        for (int r = 4; r < n; r++) {
            for (int s = r + 2; s < n; s++) {
                int c = nums[r];
                int d = nums[s];
                int g = __gcd(c, d);
                // 把商压成一个数，不用pair
                map[d / g * 1001 + c / g]++;
            }
        }
        for (int q = 2; q < n; q++) {
            for (int p = q - 2; p >= 0; p--) {
                int a = nums[p];
                int b = nums[q];
                int g = __gcd(a, b);
                ans += map[a / g * 1001 + b / g];
            }
            // 把下一轮不再合法的 r = q + 2的位置清掉（下一轮q会加1，现在的q + 2不再合法）
            for (int s = q + 4; s < n; s++) {
                int c = nums[q + 2];
                int d = nums[s];
                int g = __gcd(c, d);
                map[d / g * 1001 + c / g]--;
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二，
    枚举左，维护右，在动态维护中计数。思路应该是这样，首先(p, q)是需要一个二重循环枚举的，然后
    在这个循环中，如果还枚举r, s的话复杂度会过高，而且会重复计数，所以对每个(p, q)只考虑 r 在 q + 2的位置，
    然后向右枚举s，这样最终只有两重循环，且不重不漏。
    如果直接把所有pair算好然后去检查，即便结合二分也会多乘一个logn，不在动态中维护并检查pair，而是直接统一算好
    最后再检查，会丢失动态检查过程中能O(1)得到的r在q右边所需的范围，不得不多一个logn。
    执行用时752ms。
    */
    long long numberOfSubsequences_implementation4(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        unordered_map<double, int> count;
        for (int q = 2; q < n; q++) {
            for (int p = q - 2; p >= 0; p--) {
                // 这题1 <= nums[i] <= 1000，直接用double也没出现精度问题
                count[(double)nums[p] / nums[q]]++;
            }

            // 现在是累计了当前q左侧的所有(p, q)组合的
            // 只考虑 r = q + 2 的位置，并枚举所有右边能取的s
            // r的其它可选取值将会在后面考虑到，最终结果是不重不漏
            int r = q + 2;
            for (int s = r + 2; s < n; s++) {
                ans += count[(double)nums[s] / nums[r]];
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3404 solu;
    vector<int> nums = {1,2,3,4,3,6,1};
    cout << solu.numberOfSubsequences_implementation3(nums) << endl;
    cout << solu.numberOfSubsequences_implementation4(nums) << endl;
    return 0;
}

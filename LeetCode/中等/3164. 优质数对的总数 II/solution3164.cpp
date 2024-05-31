/*
url: https://leetcode.cn/problems/find-the-number-of-good-pairs-ii/description/
LeetCode参考: https://leetcode.cn/problems/find-the-number-of-good-pairs-ii/solutions/2790631/tong-ji-yin-zi-ge-shu-pythonjavacgo-by-e-bl3o/
相关: LeetCode3162. 优质数对的总数 I
标签: LeetCode第399场周赛, 数学, 调和级数
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3164 {
public:
    // 周赛时的解法，通过，分解因数，统计nums1的因数，然后遍历nums * k看匹配次数
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> map;
        for (int num : nums2) {
            map[num * k]++;
        }
        long long ans = 0;
        for (int num : nums1) {
            for (int i = 1; i * i <= num; i++) {
                if (num % i == 0) {
                    if (i * i == num) {
                        if (map.find(i) != map.end()) ans += map[i];
                    }
                    else {
                        if (map.find(i) != map.end()) ans += map[i];
                        if (map.find(num / i) != map.end()) ans += map[num / i];
                    }
                }
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法一，枚举nums1 / k的因子，效率要好一些。时间复杂度O(n * sqrt(U) + m)，n, m分别为nums1, nums2长度, U为nums1 / k的最大值
    long long numberOfPairs_implementation2(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> map;
        for (int num : nums2) {
            map[num]++;
        }
        long long ans = 0;
        for (int num : nums1) {
            if (num % k != 0) continue;
            num /= k;
            for (int i = 1; i * i <= num; i++) {
                if (num % i == 0) {
                    if (i * i == num) {
                        if (map.find(i) != map.end()) ans += map[i];
                    }
                    else {
                        if (map.find(i) != map.end()) ans += map[i];
                        if (map.find(num / i) != map.end()) ans += map[num / i];
                    }
                }
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法二，换一个角度，从nums2考虑，枚举nums2的倍数，然后看nums1 / k是否匹配。
    long long numberOfPairs_implementation3(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> map1;
        for (int num : nums1) {
            if (num % k == 0) {
                map1[num / k]++;
            }
        }
        int U = INT_MIN; // U为nums1 / k的最大值
        for (auto &p : map1) {
            U = max(U, p.first);
        }
        unordered_map<int, int> map2;
        for (int num : nums2) {
            map2[num]++;
        }
        long long ans = 0;
        for (auto &p : map2) {
            int num = p.first, count = p.second;
            for (int j = num; j <= U; j += num) { // 枚举num倍数
                if (map1.find(j) != map1.end()) {
                    ans += map1[j] * (long long)count;
                }
            }
        }
        /* 考虑nums2为1, 2, 3, ..., m的情况，每个数分别需要枚举U / 1, U / 2, ..., U / m次，这是个调和级数，
        为O(Ulogm)开销。这种做法总开销O(n + m + Ulogm)，实际用时比上面的方法短
        */
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3164 solu;
    vector<int> nums1 = {1, 3, 4};
    vector<int> nums2 = {1, 3, 4};
    cout << solu.numberOfPairs(nums1, nums2, 1) << endl;
    cout << solu.numberOfPairs_implementation2(nums1, nums2, 1) << endl;
    cout << solu.numberOfPairs_implementation3(nums1, nums2, 1) << endl;
    return 0;
}

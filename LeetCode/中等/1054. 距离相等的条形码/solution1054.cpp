/*
url: https://leetcode.cn/problems/distant-barcodes/description/
LeetCode参考: https://leetcode.cn/problems/distant-barcodes/solutions/2267110/ju-chi-xiang-deng-de-tiao-xing-ma-by-lee-31qt/
相关: LeetCode1953. 你可以工作的最大周数, LeetCode767. 重构字符串
标签: 构造
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1054 {
public:
    // 用`LeetCode1953. 你可以工作的最大周数`的思路来做
    vector<int> rearrangeBarcodes(const vector<int>& barcodes) {
        // 题目保证存在答案
        int n = barcodes.size();
        map<int, int, greater<int>> map; // 统计[元素值, 元素出现频率]
        for (int num : barcodes) {
            map[num]++;
        }
        vector<pair<int, int>> v;
        for (auto it = map.begin(); it != map.end(); it++) {
            v.push_back(make_pair(it->second, it->first)); // 按[元素出现频率, 元素值]放入vector
        }
        // 按频率降序排
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        vector<int> ans(n);
        int index = 0; // 目前填到了ans哪里
        for (int i = 0; i < v.size(); i++) {
            int freq = v[i].first;
            int num = v[i].second;
            while (freq > 0) {
                ans[index] = num;
                if (index == n - 2) index = 1; // 到了n - 2的位置，返回从1开始放
                else index = (index + 2) % n;
                freq--;
            }
        }
        return ans;
    }

    // 参考官方题解的做法，维护evenIndex和oddIndex，先放evenIndex，evenIndex放不下了再放oddIndex
    vector<int> rearrangeBarcodes_implementation2(const vector<int>& barcodes) {
        // 题目保证存在答案
        int n = barcodes.size();
        map<int, int, greater<int>> map;
        for (int num : barcodes) {
            map[num]++;
        }
        vector<pair<int, int>> v;
        for (auto it = map.begin(); it != map.end(); it++) {
            v.push_back(make_pair(it->second, it->first)); // 按[元素出现频率, 元素值]放入vector
        }
        // 按频率降序排
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        vector<int> ans(n);
        int evenIndex = 0; // 偶数下标填到了哪里
        int oddIndex = 1; // 奇数下标填到了哪里
        for (int i = 0; i < v.size(); i++) {
            int freq = v[i].first;
            int num = v[i].second;
            while (freq > 0) {
                if (evenIndex < n) { // 优先放evenIndex位置
                    ans[evenIndex] = num;
                    evenIndex += 2;
                }
                else {
                    ans[oddIndex] = num;
                    oddIndex += 2;
                }
                freq--;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1054 solu;
    auto a = solu.rearrangeBarcodes({1,1,1,2,2,2});
    auto b = solu.rearrangeBarcodes_implementation2({1,1,1,2,2,2});
    return 0;
}

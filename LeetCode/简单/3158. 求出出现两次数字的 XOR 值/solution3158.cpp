/*
url: https://leetcode.cn/problems/find-the-xor-of-numbers-which-appear-twice/description/
标签: LeetCode第131场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3158 {
public:
    // 周赛时还以为和LeetCode136. 只出现一次的数字一样，有什么特别的技巧可以简单算出来，结果没有，就是普通的方法
    int duplicateNumbersXOR(vector<int>& nums) {
        unordered_map<int, int> map;
        for (int num : nums) {
            map[num]++;
        }
        int ans = 0;
        for (auto &p : map) {
            if (p.second == 2) {
                ans ^= p.first;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

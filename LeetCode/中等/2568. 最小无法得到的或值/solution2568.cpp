/*
url: https://leetcode.cn/problems/minimum-impossible-or/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2568 {
public:
    /* 看[5,3,2]这个用例，位中是有1的，但是都会引入额外的1，所以1是最小不能生成的。
    再来想 [1001, 1]，1能被构成，最小不能生成为10，那[1001,1,10]呢，最小不能生成变 100 了，
    假设前面的 2^i 可以生成，那么所有 < 2^(i + 1) 的数都能生成，所以答案一定是2的幂，一个个尝试2的幂是否能被生成。
    */
    int minImpossibleOR(vector<int>& nums) {
        for (int i = 0; i < 32; i++) {
            bool found = false;
            for (int x : nums) {
                if (x == (1 << i)) found = true;
            }
            if (!found) return 1 << i;
        }
        return -1;
    }

    // 灵茶题解解法，通过 x & (x - 1) 判断是否为 2的幂 ，然后把2的幂的存在状态压缩到一个int里，然后取反求lowbit就是最小的不能生成的2的幂
    int minImpossibleOR_implementation2(vector<int>& nums) {
        int mask = 0;
        for (int x : nums) {
            if ((x & (x - 1)) == 0) {
                mask |= x;
            }
        }
        return (~mask) & -(~mask);
    }
};

int main(int argc, char const *argv[]) {
    Solution2568 solu;
    cout << solu.minImpossibleOR(*new vector<int>{2,1}) << endl;
    cout << solu.minImpossibleOR(*new vector<int>{5,3,2}) << endl;
    return 0;
}
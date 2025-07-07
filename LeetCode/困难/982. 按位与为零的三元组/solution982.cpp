/*
url: https://leetcode.cn/problems/triples-with-bitwise-and-equal-to-zero/
参考: https://leetcode.cn/problems/triples-with-bitwise-and-equal-to-zero/solutions/2145654/you-ji-qiao-de-mei-ju-chang-shu-you-hua-daxit/
标签: 【算法题单】位运算, 枚举子集
*/
#include <bits/stdc++.h>

using namespace std;

class Solution982 {
public:
    /* 灵茶题解解法一，这题1 <= nums.length <= 1000，直接枚举i, j, k会超时，
    得看数据的范围，0 <= nums[i] < 2^16，那么枚举i, j，得到的&值的个数就不会超过2^16 = 65536。
    然后再枚举k，65536 * k 不会超时

    时间复杂度 O(n * (1 << 16))。用时 187ms。
    */
    int countTriplets(vector<int>& nums) {
        int cnt[1 << 16]{};
        for (int a : nums) {
            for (int b : nums) {
                cnt[a & b]++;
            }
        }
        int ans = 0;
        for (int c : nums) {
            for (int s = 0; s < (1 << 16); s++) {
                if ((s & c) == 0) ans += cnt[s];
            }
        }
        return ans;
    }

    /* 灵茶题解解法二，不用枚举 1 << 16 的范围。nums[i] < 2^16，那么最多16位1（0xffff），
    s & c 要为0，则 s 一定为 c的补集 的子集。c的补集为 0xffff ^ c，只需要枚举 [0, 0xffff ^ c] 的所有状态(0xffff ^ c的所有子集)

    时间复杂度 O(n^2 + nU)，U为max(nums)，一个mask对应的子集状态最多为U个。用时 183ms。
    */
    int countTriplets_implementation2(vector<int>& nums) {
        int cnt[1 << 16]{};
        for (int a : nums) {
            for (int b : nums) {
                cnt[a & b]++;
            }
        }
        int ans = 0;
        for (int c : nums) {
            const int mask = c ^ 0xffff; // 能与c&得到0的s一定为mask的子集，相当于c的补集的最大状态
            int s = mask;
            do { // 枚举m的所有子集，包括空集
                ans += cnt[s];
                /* 这个 s = (s - 1) & mask 的枚举方式是精准枚举了每一个子集状态的。
                先考虑mask中间没有0的情况，例如mask==11111，则每次该 s = s - 1 ，枚举[0, 11111]就是在枚举所有子集状态。
                再来看mask中间有0的情况，例如mask==10101，10101 -> 10100 -> 10011 -> ..
                每次 & mask ，保证每次s中只有mask为1的地方有1，减1再&mask，相当于mask中间没有0的情况下的减1，
                相当于把1都往右聚拢了，精准地枚举了mask对应的所有子集。

                灵茶题解中提到：这一技巧经常用于子集状压 DP 中。
                */
                s = (s - 1) & mask;
            } while (s != mask); // 循环的结束条件为s变成-1，此时 -1 & mask == mask，可以用 s != mask 控制循环退出，但是这样一开始时s==mask，直接退出了，所以写do-while
            
            // 也可以这样写，要好记一点，注意要在 & mask前判断，不然 -1 & mask又变正数了：
            /* while (true) {
                ans += cnt[s];
                if (s == 0) break; // s为空集，已经被计数了，s - 1为负，不用再循环了
                s = (s - 1) & mask;
            }    */     
        }
        return ans;
    }

    /* 灵茶题解解法三，上一种解法是枚举c，求(a & b) & c == 0的(a & b)的个数。也可以写成枚举a, b，求 (a & b) & c == 0的c的个数

    时间复杂度 O(n^2 + nU)。用时 135ms。
    */
    int countTriplets_implementation3(vector<int>& nums) {
        int cnt[1 << 16]{};
        // nums[i]作为c，与哪些值 & 的结果为0，刷表法，c去刷表
        for (int c : nums) {
            int mask = c ^ 0xffff; // c的补集的最大状态，求其所有子集（包括空集，因为空集代表 a & b == 0，则 a & b & c 也是为0的）
            int s = mask;
            while (true) {
                cnt[s]++; // 如果 (a & b) 能为 s 的话，能找到一个c，使得 a & b & c == 0
                if (s - 1 < 0) break;
                s = (s - 1) & mask;
            }
        }

        int ans = 0;
        for (int a : nums) {
            for (int b : nums) {
                ans += cnt[a & b];
            }
        }
        return ans;
    }

    /* 灵茶题解解法四，灵神还在优化！
    实际计算一下，把0xffff换成实际的上界。

    时间复杂度 O(n^2 + nU)。用时 15ms。
    */
    int countTriplets_implementation4(vector<int>& nums) {
        int U = 1;
        for (int x : nums) while (U <= x) U <<= 1; // 全集为 U - 1，用 U - 1 替换 0xffff

        int cnt[1 << 16]{};
        for (int c : nums) {
            int mask = c ^ (U - 1);
            int s = mask;
            while (true) {
                cnt[s]++;
                if (s - 1 < 0) break;
                s = (s - 1) & mask;
            }
        }

        int ans = 0;
        for (int a : nums) {
            for (int b : nums) {
                ans += cnt[a & b];
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution982 solu;
    cout << solu.countTriplets(*new vector<int>{2,1,3}) << endl;

    cout << solu.countTriplets_implementation2(*new vector<int>{2,1,3}) << endl;

    cout << solu.countTriplets_implementation3(*new vector<int>{2,1,3}) << endl;

    cout << solu.countTriplets_implementation4(*new vector<int>{2,1,3}) << endl;
    return 0;
}
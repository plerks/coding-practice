/*
url: https://leetcode.cn/problems/maximum-subarray-with-equal-products/description/
参考: https://leetcode.cn/problems/maximum-subarray-with-equal-products/solutions/3039079/mei-ju-ti-qian-tui-chu-xun-huan-pythonja-a21k/
标签: LeetCode第431场周赛, 数学, 数论, 滑动窗口, 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3411 {
public:
    /* 周赛时的写法，通过，不过写得很暴力。
    当只有两个数时，x * y = lcm(x, y) * gcd(x, y)是一定成立的，
    当有多个数时(n>=3)，lcm和gcd都满足结合律，即gcd(a, b, c) = gcd(gcd(a, b), c) = gcd(a, gcd(b, c))，
    设gcd(x1, x2, ..., xn) = g，
    则 x1 * x2 *...* xn = g * lcm(x1, x2, ..., xn)等价于
    g^n * (y1 * y2 * ... * yn) = g * lcm(g * y1, g * y2, ..., g * yn) = g^2 * lcm(y1 * y2 * ... * yn)
    左边两个因数都是 >= 右边两个因数的，所以要有 g^n = g^2 (g等于1)，(y1 * y2 * ... * yn) = lcm(y1 * y2 * ... * yn)，
    于是 原等式成立 等价于 xi两两互质
    更详细地来说:
        假设n = k - 1时成立，则n = k时，
        已知g=1，所以各个xi=yi，只需证明yk和前面的yi(i<k)都互质即可。由于前面都已经两两互质了，所以yk也必须与他们互质，不然右边
        的lcm就会比左边少乘质因子
    */
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 2;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (j - i + 1 == 2) continue; // 两个数一定成立
                // 让它们两两互质
                bool check = true;
                for (int x = i; x <= j; x++) {
                    for (int y = x + 1; y <= j; y++) {
                        if (std::__gcd(nums[x], nums[y]) != 1) {
                            check = false;
                        }
                    }
                }
                if (check) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法一
    这题2 <= nums.length <= 100，1 <= nums[i] <= 10，直接暴力求的话所有nums[i]的乘积会爆long long。
    数越多，乘积会变大，lcm会变大，gcd会变小，先求nums所有数的lcm(最大值)，当乘积m > all_lcm * gcd时，再加数
    只会让左边变大，右边变小，而all_lcm >= partial_lcm，则一定达不成相等，1~10的lcm和gcd都不大，则可以提前退出，这样就不会溢出
    */
    int maxLength_implementation2(vector<int>& nums) {
        int n = nums.size();
        int all_lcm = 1;
        // std::gcd和std::lcm需要c++17
        for (int x : nums) all_lcm = std::lcm(all_lcm, x);
        int ans = 2;
        for (int i = 0; i < n; i++) {
            // 注意初值的选择，任何数与1的lcm是它本身，任何数与0的gcd是它本身
            int m = 1, gcd = 0, lcm = 1;
            for (int j = i; j < n; j++) {
                int x = nums[j];
                m *= x;
                gcd = std::gcd(gcd, x);
                lcm = std::lcm(lcm, x);
                if (m > all_lcm * gcd) break;
                if (m == lcm * gcd) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二
    题解里证明等式成立的条件是两两互质的方式有所不同，考虑的是对某个素因子p的指数，
    prod(arr) == lcm(arr) * gcd(arr)，则e1 + e2 +...+ ei = min(e1, e2, ...,ei) + max(e1, e2, ..., ei)，
    分情况讨论后ei至少要有n - 1个为0，于是两两互质。

    然后用滑窗来找两两互质，最开始区间为空时满足两两互质，然后只需考虑新加进来的
    */
    int maxLength_implementation3(vector<int>& nums) {
        int ans = 2, mul = 1, left = 0;
        // 不需要O(n^2)一个个试，考虑nums[right]和前面的数的乘积的互素性，这样就有单调性
        // 前面的数两两互素，所以nums[right]与前面都互素 等价于 nums[right]与乘积互素
        for (int right = 0; right < nums.size(); right++) {
            while (std::gcd(mul, nums[right]) > 1) {
                mul /= nums[left];
                left++;
            }
            mul *= nums[right]; // 这里不会溢出，出现重复数字就不再两两互素了
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3411 solu;
    cout << solu.maxLength(*new vector<int>{1,2,1,2,1,1,1}) << endl;
    cout << solu.maxLength_implementation2(*new vector<int>{1,2,1,2,1,1,1}) << endl;
    cout << solu.maxLength_implementation3(*new vector<int>{1,2,1,2,1,1,1}) << endl;
    return 0;
}

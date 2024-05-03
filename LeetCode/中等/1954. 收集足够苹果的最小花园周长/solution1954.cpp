/*
url: https://leetcode.cn/problems/minimum-garden-perimeter-to-collect-enough-apples/description/
相关: LeetCode3102. 最小化曼哈顿距离
标签: 数学, 二分查找
*/

#include <bits/stdc++.h>

using namespace std;

// 这题的竖着的正方形和横着的正方形是到原点的曼哈顿距离和切比雪夫距离为C的点，有点像`LeetCode3102. 最小化曼哈顿距离`，不过两题技巧不同

class Solution1954 {
public:
    /* 明显可以二分，问题的关键在于，假设正方形的右上角坐标为(n, n)，那么整个正方形格点上的苹果数目是多少？
    这个计算很繁琐，见`计算苹果数.md` */
    long long minimumPerimeter(long long neededApples) {
        int left = 1, right = 100000;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (4LL * f(mid) < neededApples) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        // left为第一个总苹果数>=neededApples的右上角坐标(left, left)
        return 8 * left;
    }

    long long f (long long n) {
        // return (n * (n + 1) * (2 * n + 1)) / 3 + n * n + n + ((2 * n + 1) * (3 * n + 2) * (n - 1)) / 2 - (n * (2 * n + 1) * (4 * n + 1)) / 3 + (n + 1) * (n + 1);
        // return (2 * n * n * n + 3 * n * n + n) / 2;
        return (n * (n + 1) * (2 * n + 1)) / 2;
    }
};

int main(int argc, char const *argv[]) {
    Solution1954 solu;
    cout << solu.minimumPerimeter(1) << endl;
    cout << solu.minimumPerimeter(13) << endl;
    cout << solu.minimumPerimeter(1000000000) << endl;
    return 0;
}
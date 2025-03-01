/*
url: https://leetcode.cn/problems/maximize-the-distance-between-points-on-a-square/
参考: https://www.bilibili.com/video/BV1hiAUeWEUG/
      https://leetcode.cn/problems/maximize-the-distance-between-points-on-a-square/solutions/3086167/zhuan-cheng-qie-bi-xue-fu-ju-chi-er-fen-nthy1/
标签: LeetCode第438场周赛, 曼哈顿距离, 二分, 倍增
*/

// 这次周赛一题

#include <bits/stdc++.h>

using namespace std;

class Solution3464 {
public:
    /* 灵茶题解解法一，
    从(0, 0)开始，顺时针按移动距离把正方形拉成一条线，然后记录"前进距离"，记为a，
    由于本题k>=4，所以ans一定<=side，二分的范围也会<=side，于是，由于二分check的下限low<=side，见`./到S点的曼哈顿距离变化.png`，
    若下一个点在两个拐角之内(SB + BC)，而在SB + BC的范围内，拉成一条线的前进距离刚好等于曼哈顿距离，所以二分a中 > 下限low
    的第一个位置，二分的就是曼哈顿距离，若还没满足的，则在CD上时，虽然前进距离不等于曼哈顿距离，但是由于check的下限low < side，
    这部分也是一定满足的，不满足的是，距离S逆时针的前进距离 < low 的范围内（前进距离 > 4 * side + low），这时虽然a中记录的前进距离很大，
    但是由于其不是曼哈顿距离，是不符合下限要求的！所以还需检测是否 前进距离 > 4 * side + low。
    此外，这里每次下一步选最近的符合的点，是在贪心。

    如果这题k<=3，这样做就有问题，这时二分check的下限low很大，如果当前在A点，对a二分找到C点，C点被找到是由于其“前进距离”大，
    但是其实际的曼哈顿距离不一定>=low，这样就会有问题。

    时间复杂度O(nlogn + log(4side/k) * nklogn)，n为points长度
    */
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> a; // 到原点的前进距离
        for (auto &p : points) {
            int x = p[0], y = p[1];
            if (x == 0) a.push_back(y);
            else if (y == side) a.push_back(side + x);
            else if (x == side) a.push_back(2LL * side + side - y);
            else a.push_back(3LL * side + side - x);
        }
        sort(a.begin(), a.end());

        auto check = [&](int low) -> bool {
            /* 枚举起点，注意，这里不需要考虑比方说从a的back()为第一个点，下一个点需要回到a的开头的
            情况，因为这会在枚举这个点为起点时被考虑。所以不需要把a当做循环数组来二分。
            */
            for (long long start : a) { // 枚举起点
                long long cur = start;
                long long end = start + 4LL * side - low;
                for (int i = 0; i < k - 1; i++) { // 再找k - 1个点
                    auto it = lower_bound(a.begin(), a.end(), cur + low); // 这个二分的结果被套在了两层循环里，但是与内层循环无关，可以预先处理进行记忆化
                    if (it == a.end() || (*it) > end) {
                        cur = -1; // 这个起点不行，用cur = -1来记录是异常退出的
                        break;
                    }
                    cur = *it;
                }
                if (cur >= 0) return true;
            }
            return false;
        };

        int left = 0, right = side * 4LL / k;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }

    // 待做: 这题灵茶题解还有其它解法，有个用倍增的解法，这样就算k给得很大时，时间复杂度里的k不是直接的乘积因子，而是logk为乘积因子
};

int main(int argc, char const *argv[]) {
    Solution3464 solu;
    cout << solu.maxDistance(2, *new vector<vector<int>>{{0,0},{1,2},{2,0},{2,2},{2,1}}, 4) << endl;
    return 0;
}
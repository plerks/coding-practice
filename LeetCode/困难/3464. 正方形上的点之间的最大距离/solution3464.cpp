/*
url: https://leetcode.cn/problems/maximize-the-distance-between-points-on-a-square/
参考: https://www.bilibili.com/video/BV1hiAUeWEUG/
      https://leetcode.cn/problems/maximize-the-distance-between-points-on-a-square/solutions/3086167/zhuan-cheng-qie-bi-xue-fu-ju-chi-er-fen-nthy1/
标签: LeetCode第438场周赛, 曼哈顿距离, 二分, 倍增, 指针优化二分, 多指针优化二分
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

    /* 灵茶题解，用k指针优化解法一，不知道算不算指针优化二分的典型套路，用k个指针移动优化解法一中的反复二分查找，
    具体来说，把k个指针都记录起来，枚举n个起点的过程中，这k个指针都会单调往右滑，
    这样check的复杂度就是nk，而不是nklogn。

    时间复杂度O(nlogn + log(4side/k) * nk)
    */
    int maxDistance_implementation2(int side, vector<vector<int>>& points, int k) {
        vector<long long> a;
        for (auto &p : points) {
            int x = p[0], y = p[1];
            if (x == 0) a.push_back(y);
            else if (y == side) a.push_back(side + x);
            else if (x == side) a.push_back(2LL * side + side - y);
            else a.push_back(3LL * side + side - x);
        }
        sort(a.begin(), a.end());
        int n = a.size();

        auto check = [&](int low) -> bool {
            vector<int> idx(k); // k指针
            for (int i = 0; i < n; i++) {
                idx[0] = i; // 起点
                // 剩余k-1个指针滑动
                for (int j = 1; j < k; j++) {
                    while (a[idx[j]] - a[idx[j - 1]] < low) {
                        idx[j]++;
                        if (idx[j] == n) return false; // 这时可以return false了，后面也一定无法找到k个相邻够远的点
                    }
                }
                // 相邻距离够远的约束满足，检查首尾约束
                if (4LL * side - (a[idx[k - 1]] - a[idx[0]]) >= low) return true;
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

    /* 灵茶题解，k指针还能再优化，
    a[0]下一个距离>=low的点是j，那么开头的点只需枚举[0, j)即可。
    因为，若以>=j的位置i开头，可以得到完全合法的长度为k的链 i, ... , j，
    则 0, i, ... , j - 1 也一定是合法的，一方面，这条链满足相邻相距>=low的约束，
    另一方面，由于dis(j, j - 1)>=low，而0, j, j - 1的逆时针顺序为0, j, j - 1，
    那么dis(0, j - 1)>=low，所以，0, i, ... , j - 1 完全合法！
    神奇！枚举开头只需要考虑 [0, 第一个>=a[0]+low的点) 间的点，也就是说选第一段间的点来枚举作为开头点就行！

    时间复杂度O(nlogn + log(4side/k) * nk)
    */
    int maxDistance_implementation3(int side, vector<vector<int>>& points, int k) {
        vector<long long> a;
        for (auto &p : points) {
            int x = p[0], y = p[1];
            if (x == 0) a.push_back(y);
            else if (y == side) a.push_back(side + x);
            else if (x == side) a.push_back(2LL * side + side - y);
            else a.push_back(3LL * side + side - x);
        }
        sort(a.begin(), a.end());
        int n = a.size();

        auto check = [&](int low) -> bool {
            vector<int> idx(k); // k指针
            // 先用klogn时间跑一遍a[0]作为开头选的点。这样每个指针有个基础的位置，不用都从0开始。
            long long cur = a[0];
            for (int i = 1; i < k; i++) {
                int j = lower_bound(a.begin(), a.end(), cur + low) - a.begin();
                if (j == n) return false;
                idx[i] = j;
                cur = a[j];
            }
            if (4LL * side - (a[idx[k - 1]] - a[idx[0]]) >= low) return true;

            for (int i = 0; i < idx[1]; i++) {
                idx[0] = i;
                for (int j = 1; j < k; j++) {
                    while (a[idx[j]] - a[idx[j - 1]] < low) {
                        idx[j]++;
                        if (idx[j] == n) return false;
                    }
                }
                if (4LL * side - (a[idx[k - 1]] - a[idx[0]]) >= low) return true;
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

    /* 待做: 这题灵茶题解还有其它解法，有个用倍增的解法，这样就算k给得很大时，时间复杂度里的k不是直接的乘积因子，而是logk为乘积因子。
    多指针一位位移动还是太慢，能用倍增把时间复杂度优化为O(nlogn + log(4side/k) * nlogk)
    */

    /* 最优的dp解法，考虑用f[i]表示以i开头，相邻点相距>=low的链的最大长度，这个定义没检查首尾相距要够远的合法性，
    所以发现链够长后要检查。递推的方式是贪心，对i，找右侧第一个>=low的点i'，则f[i] = f[i'] + 1，而这通过双指针，
    只需要线性时间即可做到。
    
    巧妙的是，这题不需要考虑f[i]>k的情况，例如，f[i]=k+1，f[i']=k，f[i']的链尾记作end，
    如果i能成为正解，说明dis(i, i') >= low，而i', i, end的逆时针顺序是i', i, end，那么一定也有dis(i', end) >= low，
    f[i']时就已经返回了true！所以不需要考虑f[i] > k的情况。不需要有这样的忧虑：当我发现f[i]=k+1但是首尾点相距太近，
    需要把end前进一步，将f[i]的链变为 i, i', ... , end-1 ，再去检查首尾距离。这是不需要的，很奇妙！

    时间复杂度O(nlogn + nlog(4side/k))，check的时间复杂度与k无关了，只要O(n)，最优的做法。
    */
    int maxDistance_implementation4(int side, vector<vector<int>>& points, int k) {
        vector<long long> a; // 到原点的前进距离
        for (auto &p : points) {
            int x = p[0], y = p[1];
            if (x == 0) a.push_back(y);
            else if (y == side) a.push_back(side + x);
            else if (x == side) a.push_back(2LL * side + side - y);
            else a.push_back(3LL * side + side - x);
        }
        sort(a.begin(), a.end());

        int n = a.size();
        vector<int> f(n + 1); // 以i开头的最大长度，f保证的合法性是相邻点相距>=low
        vector<int> end(n); // 每条链的末端点

        auto check = [&](int low) {
            int j = n;
            for (int i = n - 1; i >= 0; i--) {
                while (a[j - 1] - a[i] >= low) j--;
                f[i] = f[j] + 1;
                if (f[i] == 1) end[i] = i;
                else end[i] = end[j];
                if (f[i] == k && 4LL * side - (a[end[i]] - a[i]) >= low) return true;
            }
            return false;
        };

        int left = 1, right = side * 4LL / k;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
};

int main(int argc, char const *argv[]) {
    Solution3464 solu;
    cout << solu.maxDistance(2, *new vector<vector<int>>{{0,0},{1,2},{2,0},{2,2},{2,1}}, 4) << endl;
    cout << solu.maxDistance_implementation2(2, *new vector<vector<int>>{{0,0},{1,2},{2,0},{2,2},{2,1}}, 4) << endl;
    cout << solu.maxDistance_implementation3(2, *new vector<vector<int>>{{0,0},{1,2},{2,0},{2,2},{2,1}}, 4) << endl;
    cout << solu.maxDistance_implementation4(2, *new vector<vector<int>>{{0,0},{1,2},{2,0},{2,2},{2,1}}, 4) << endl;
    cout << solu.maxDistance_implementation4(2, *new vector<vector<int>>{{0,0},{0,1},{0,2},{1,2},{2,0},{2,2},{2,1}}, 5) << endl;
    return 0;
}
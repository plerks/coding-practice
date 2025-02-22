/*
url: https://leetcode.cn/problems/separate-squares-i/
参考: https://www.bilibili.com/video/BV1BRAGevERN/
      https://leetcode.cn/problems/separate-squares-i/solutions/3076424/zheng-shu-er-fen-pythonjavacgo-by-endles-8yn5/
相关: LeetCode3454. 分割正方形 II
标签: LeetCode第150场双周赛, 浮点数二分, 试填法, 差分, 扫描线, 矩形面积并
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3453 {
public:
    /* 周赛时的解法，通过，思路是先用整数的二分找出下界y，这样真实答案一定在(y, y+1]之间，然后用试填法计算小数位，
    然后这题范围很大，最多5 * 10^4个边长为1e9的正方形，面积之和会爆long long，所以得把int128都用出来。
    注意二分时得 搜索区间内最后一个下面积 < 总面积/2 而不能 最后一个下面积 <= 总面积/2，因为试填时是填上小数位变大，
    例如[1, 2]中间没有正方形，这个区间都能二分面积，搜索<=会得到2，然后试填结果是2.00000，不是最小的二分面积的y。
    */
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        __int128_t left = 0, right = 2e9;
        // 搜索区间内最后一个下面积 < 总面积/2
        __int128_t total = 0;
        for (auto &vec : squares) {
            total += (__int128_t)vec[2] * vec[2];
        }
        double epsilon = 0.00001;

        auto check1 = [&](int p) {
            __int128_t sum = 0;
            for (auto &vec : squares) {
                int x = vec[0], y = vec[1], l = vec[2];
                if (p > y) {
                    sum += min(l, (p - y)) * (__int128_t)l;
                }
            }
            return sum < total / 2.0;
        };

        while (left <= right) {
            __int128_t mid = (left + right) / 2;
            if (check1(mid)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }

        auto check2 = [&](double p) {
            double sum = 0;
            for (auto &vec : squares) {
                int x = vec[0], y = vec[1], l = vec[2];
                if (p > y) {
                    sum += min((double)l, (p - y)) * l;
                }
            }
            return sum < total / 2.0;
        };
        
        double r = right;
        double base = 0.1;
        // 用试填法确定5位小数，这样例如输出1.16666而真实答案是1.166669999...，和真实答案的差距也在1e-5之内
        for (int i = 0; i < 5; i++) {
            double t = r;
            for (int d = 0; d <= 9; d++) {
                if (check2(r + d * base)) t = r + d * base;
                else break;
            }
            r = t;
            base /= 10;
        }
        return r;
    }

    /* 参考灵茶题解，这题题目范围总面积太大，实际还是有浮点数舍入误差的问题的，当到达1e16级别时，1e16+1将会==1e16，
    如下：
    ```
    double x1 = 1e16;
    double x2 = 1e16 + 1;
    x2++;
    x2++;

    // 直接写 cout << bitset<32>(x1).to_string() << endl; 由于bitset的构造函数，x1会转成整数，当x1==0.5时会输出全0，得用reinterpret_cast
    cout << bitset<32>(*reinterpret_cast<long long*>(&x1)).to_string() << endl;

    cout << bitset<32>(*reinterpret_cast<long long*>(&x2)).to_string() << endl;

    cout << (x1 == x2) << endl;

    // 浮点数能表示的数有间隔，std::nextafter(x, y)用于计算x在往y方向上走的下一个浮点数，y比x大往更大走，y比x小往更小走
    double next = std::nextafter(1e16, DBL_MAX);
    double prev = std::nextafter(1e16, 0);
    cout << bitset<32>(*reinterpret_cast<long long*>(&next)).to_string() << endl;
    cout << bitset<32>(*reinterpret_cast<long long*>(&prev)).to_string() << endl;
    ```
    灵神视频讲解了浮点数这一点，并提了个hack，在y较小时用大量的大边长正方形把总面积积累到1e16的数量级，然后再在上面
    放极大量的边长为1的正方形，这样在计算总面积时，浮点数的舍入误差会导致+1不变，这样计算总面积就是严重错误的。
    这样就导致浮点数完全用不了，得用高精度的整数。
    所以，LeetCode后面在题目范围上加了限制：The total area of all the squares will not exceed 10^12

    灵茶题解解法一，用浮点数二分，并用循环次数控制精度。这题搜索区间为2e9，精度要满足 2e9 / 2^k <= 1e-5，k > log(2*10^14)，
    k大概要33次，但是实际只33次有用例过不了。
    浮点数二分不是不能直接用，但是题目范围不能太大。
    */
    double separateSquares_implementation2(vector<vector<int>>& squares) {
        double total = 0;
        int maxY = 0;
        double left = 0, right = 0;
        for (auto &sq : squares) {
            total += 1LL * sq[2] * sq[2];
            maxY = max(maxY, sq[1] + sq[2]);
        }
        right = maxY;

        auto check = [&](double p) {
            double sum = 0;
            for (auto &vec : squares) {
                int x = vec[0], y = vec[1], l = vec[2];
                if (p > y) {
                    sum += min((double)l, (p - y)) * l;
                }
            }
            return sum < total / 2.0;
        };

        /* 注意，这里浮点数二分就必须用开区间写法了。其它的比如闭区间写法，都是建立在整数连续的前提下的，
        对于浮点数二分，在left = mid + 1这个+1上就是错的，比如在1.5是最后一个回答'是'的位置，
        当前区间是[1, 2]，那么check(1.5)后left会变成2，结果会认为1是最后一个'是'的位置，归根结底
        是1的跨度对于浮点数来说太大，对于整数连续的情景是没有问题的。
        此外，这里最好用循环次数来控制，写 while (right - left > 2 * 1e-5) 之类的能过，但可能有精度问题然后算出left==mid，然后死循环。
        */
        for (int i = 0; i < 47; i++) {
            double mid = (left + right) / 2;
            if (check(mid)) left = mid;
            else right = mid;
        }
        return (left + right) / 2; // 取区间中点
    }

    /* 灵茶题解解法二，转化成整数二分，写法一。
    要找area * 2 >= total的第一个位置y，转换成找 y * 1e5 的位置，最后再除以1e5即可。这样就可以全程用整数计算。
    */
    double separateSquares_implementation3(vector<vector<int>>& squares) {
        long long total = 0;
        int maxY = 0;
        long long left = 0, right = 0;
        for (auto &sq : squares) {
            total += 1LL * sq[2] * sq[2];
            maxY = max(maxY, sq[1] + sq[2]);
        }
        const int M = 1e5;
        right = (long long)maxY * M;

        /* Σmin(l, (y - yi)) * l >= total / 2 变成
        Σmin(l, (y*M/M - yi)) * l >= total / 2，再变成
        Σmin(l*M, (y*M - yi * M)) * l * 2 >= total * M，y*M就是二分的目标对象multi_y
        */
        auto check = [&](long long multi_y) {
            long long sum = 0;
            for (auto &vec : squares) {
                long long x = vec[0], y = vec[1], l = vec[2];
                if (multi_y > y * M) {
                    sum += min(l * M, multi_y - y * M) * l * 2;
                }
            }
            return sum >= total * M;
        };

        while (left + 1 < right) {
            long long mid = (left + right) / 2;
            if (!check(mid)) left = mid;
            else right = mid;
        }
        return right / (double)M;
    }

    /* 灵茶题解解法二，转化成整数二分，写法二。
    不用乘M也能转化成全为整数的运算，先整数二分找出答案所在的长为1的区间，然后，由于正方形都在整数的位置，
    因此，在(y - 1, y]的范围内，面积随y一定是线性变化的！(面积随y增大是分段线性的函数，每段长度至少为1)，
    只需要找出底边长即可直接计算小数部分！
    */
    double separateSquares_implementation3(vector<vector<int>>& squares) {
        long long total = 0;
        int maxY = 0;
        int left = 0, right = 0;
        for (auto &sq : squares) {
            total += 1LL * sq[2] * sq[2];
            maxY = max(maxY, sq[1] + sq[2]);
        }
        right = maxY;

        auto calc_area = [&](int p) {
            long long sum = 0;
            for (auto &vec : squares) {
                long long x = vec[0], y = vec[1], l = vec[2];
                if (p > y) {
                    sum += min(l, p - y) * l;
                }
            }
            return sum;
        };

        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (calc_area(mid) * 2 < total) left = mid;
            else right = mid;
        }
        int y = right;
        // 现在right是第一个下方面积>=total/2的位置，正确答案在(y-1, y]之间
        long long area_y = calc_area(y);
        int k = area_y - calc_area(y - 1); // 这样就算出了(y-1, y]的正方形的底边之和
        return y - (area_y - total / 2.0) / k;
    }

    /* 灵茶题解解法三，用差分数组 + 扫描线。
    正方形最多5 * 10^4个，所以差分数组元素在1e5的数量级，并不大，
    用差分数组记录在某个y处的底边长之和，就可以知道当前的斜率了，很巧妙的解法。
    */
    double separateSquares_implementation4(vector<vector<int>>& squares) {
        map<int, long long> diff;
        long long total = 0;
        for (auto &sq : squares) {
            int y = sq[1], l = sq[2];
            total += 1LL * sq[2] * sq[2];
            diff[y] += l;
            diff[y + l] -= l;
        }
        long long area = 0, sum_k = 0; // sum_k为当前底边长度之和，代表当前的斜率
        // 顺序遍历突变点
        for (auto it = diff.begin();;) {
            auto &[y, dk] = *it;
            int y2 = (++it)->first;
            sum_k += dk;
            area += (y2 - y) * sum_k;
            if (area * 2 >= total) {
                return y2 - (area - total / 2.0) / sum_k;
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3453 solu;
    //cout << solu.separateSquares(*new vector<vector<int>>{{0,0,1},{2,2,1}}) << endl;
    //cout << solu.separateSquares(*new vector<vector<int>>{{0,0,2},{1,1,1}}) << endl;

    cout << solu.separateSquares_implementation2(*new vector<vector<int>>{{0,0,1},{2,2,1}}) << endl;
    cout << solu.separateSquares_implementation2(*new vector<vector<int>>{{0,0,2},{1,1,1}}) << endl;
    return 0;
}
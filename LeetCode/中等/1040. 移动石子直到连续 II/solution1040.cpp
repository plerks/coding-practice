/*
url: https://leetcode.cn/problems/moving-stones-until-consecutive-ii/
参考: https://leetcode.cn/problems/moving-stones-until-consecutive-ii/solutions/2212638/tu-jie-xia-tiao-qi-pythonjavacgo-by-endl-r1eb/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1040 {
public:
    /* 参考灵茶题解，
    首先考虑最大值，如果第一步动的是最右边石子，那么放到最右的合法空位里，然后最右的段就一定有>=2颗石子，
    然后以类似跳棋的方式，这样能每步让最右的段左移最少的一步，
    这样步数为 [s[0], s[n-2]] 的空位数量，
    如果第一步动的是最左边石子，步数为 [s[1], s[n-1]] 的空位数量，二者取大值。
    具体的跳棋方式大概如此：
    1 4 5 8 10
    4 5 6 8 10
    5 6 7 8 10
    6 7 8 9 10

    然后考虑最小值，尽量让石子一步到位，变成长度为n的窗口，最少多少个空位(转换成最多多少个石子)。
    也就是求窗口最小空位数，但是，"最小窗口"可能是非法的，
    像 1 6 7 8 这种排布，1不能直接挪到5的位置，得先把 8 -> 4，然后 1 -> 5。
    也即，窗口外石子全在窗口的单侧时，结论需要调整，
    注意，像 1 6 7 8 10 这种排布，是符合结论的，排成4 5 6 7 8即可。
    如何判断单侧的特殊情况？
    有n-1个元素连着，也即[s[0], s[n-2]]或[s[1], s[n-1]]连着，这时可能需要2步，也可能0步，1步（例如 5 6 7 8 和 4 6 7 8），
    与maxMove取min即可。
    窗口两侧都有石子，是否一定能在空位数操作次数下移动成连续？
    像 xxx    _x_x_x_    x 这样，先填边缘空位，然后填内部空位即可
    像 xxx    __xxx__    x 这样，也是ok的，让两个外侧各剩一个石子，然后还剩2个空位，错着放就能保证合法性

    这题很有意思，能想到要看内部的空位数，考虑过用长为n的窗口找空位数以及最大最小的策略可能不一样，但是答案不是这么简单就能分析清楚的。
    */
    vector<int> numMovesStonesII(vector<int>& s) {
        int n = s.size();
        sort(s.begin(), s.end());
        int mx = max(s[n - 2] - s[0] + 1 - (n - 1), s[n - 1] - s[1] + 1 - (n - 1));
        int mi = n;
        if (s[n - 2] - s[0] == n - 2 || s[n - 1] - s[1] == n - 2) {
            mi = min(2, mx);
        }
        else {
            int l = 0;
            for (int r = 0; r < n; r++) {
                while (s[r] - s[l] + 1 > n) l++;
                mi = min(mi, n - (r - l + 1));
            }
        }
        return {mi, mx};
    }
};

int main(int argc, char const *argv[]) {
    Solution1040 solu;
    // auto a = solu.numMovesStonesII(*new vector<int>{7,4,9});
    auto b = solu.numMovesStonesII(*new vector<int>{6,5,4,3,10});
    return 0;
}
/*
url: https://leetcode.cn/problems/airplane-seat-assignment-probability/description/?envType=daily-question&envId=2024-10-04
参考: https://leetcode.cn/problems/airplane-seat-assignment-probability/solutions/664495/fei-ji-zuo-wei-fen-pei-gai-lu-by-leetcod-gyw4/
我的题解: https://leetcode.cn/problems/airplane-seat-assignment-probability/solutions/2938943/guan-yu-guan-fang-ti-jie-suo-shuo-de-yan-3mw4/
标签: 数学
*/

class Solution1227 {
public:
    double nthPersonGetsNthSeat(int n) {
        /* 设第n个人坐在自己座位上的概率为an
        第一个人有3种情况，选1位置，则第n个人坐在自己座位上的概率为 1/n * 1
        选n位置，则概率为1/n * 0
        选中间位置x(1 < x < n)，则将第x人视作其正确座位在1号座位，则问题回到一开始的状态，只是规模变为n-1，概率为(n-2)/n * a(n-1)
        于是an = 1/n + (n-2)/n*a(n-1)，变形为nan = (n-2)a(n-1) + 1，这个可以从a2 = 1/2归纳得到后面都是1/2，要求通项的话：
        两边同时乘n - 1，变为 n(n-1)an = (n-1)(n-2)a(n-1) + n - 1，设bn = n(n-1)an，
        则有 bn = b(n-1) + n - 1，b1 = 0，然后能解出来 bn = n(n-1)/2 (n >= 2), b1 = 0，综合起来 bn = n(n-1)/2 (n >= 1)
        于是 an = 1/2 (n >= 2), a1 = 0

        解 bn = b(n-1) + n - 1 可以通过展开写下去，也可以待定系数 bn + An^2 + Bn + C = b(n-1) + A(n-1)^2 + B(n-1) + C,
        这里得设成2次多项式，1次还不行
        */
        if (n == 1) return 1;
        return 0.5;
    }

    /* 补充: 上面这样想并不严谨，官方题解的做法是严谨的，具体见`我的题解.md`。
    这里只保留f(n) = 1/n * 1 + 1/n * 0 + 1/nΣ(i=2, n - 1)f(n-i+1)是怎么计算的:
    nf(n) = 1 + Σ(i=2, n - 1)f(n-i+1), 再写一项
    (n-1)f(n-1) = 1 + Σ(i=2, n - 2)f(n-i) = 1 + Σ(i=3, n - 1)f(n-i+1)
    两边相减能得到f(n) = f(n-1)，这样就能得到结果了。
    */
};

int main(int argc, char const *argv[]) {
    return 0;
}

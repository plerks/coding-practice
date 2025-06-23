/*
描述: 数论的小omega函数ω(n)指：n的不同质因数的个数（不计重复），例如，ω(18) = ω(2 × 3²) = |{2, 3}| = 2。
      如果只需要计算一个数的omega函数值，则对其质因数分解就行。这里写的是如何预处理一定范围内的数的omega函数值，方法类似筛。
      当要读取的omega值较多时，每次花sqrt(i)时间计算，总时间约为 sqrt(1) + sqrt(2) + ... + sqrt(mx)。不如花O(mx)时间提前预处理出来。
参考: https://en.wikipedia.org/wiki/Prime_omega_function
相关: LeetCode2818. 操作使得分最大
*/
#include <iostream>

const int MX = 1e5 + 1;

int omega[MX]; // 小omega函数，表示n的不同质因数个数

auto init = []() {
    for (int i = 2; i < MX; i++) {
        if (omega[i] == 0) { // i是质数
            for (int j = i; j < MX; j += i) {
                omega[j]++; // i是j的一个质因子
            }
        }
    }
    return 0;
}();

int main(int argc, char const *argv[]) {
    for (int i = 2; i <= 18; i++) {
        std::cout << "ω(" << i << "): " << omega[i] << std::endl;
    }
    return 0;
}
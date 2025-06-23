/*
描述: 数论的大omega函数Ω(n)指：n的质因数总个数（包括重复），例如，Ω(18) = Ω(2 × 3²) = 1 + 2 = 3。
      如果只需要计算一个数的omega函数值，则对其质因数分解就行。这里写的是如何预处理一定范围内的数的omega函数值，方法类似筛。
参考: https://en.wikipedia.org/wiki/Prime_omega_function
*/
#include <iostream>

const int MX = 1e5 + 1;

int omega[MX]; // 大omega函数，表示n的质因数总个数

auto init = []() {
    for (int i = 2; i < MX; i++) {
        if (omega[i] == 0) { // i是质数
            for (int j = i; j < MX; j += i) {
                int t = j;
                while (t % i == 0) { // i是t的一个质因子
                    omega[j]++;
                    t /= i;
                }
            }
        }
    }
    return 0;
}();

int main(int argc, char const *argv[]) {
    for (int i = 2; i <= 18; i++) {
        std::cout << "Ω(" << i << "): " << omega[i] << std::endl;
    }
    return 0;
}
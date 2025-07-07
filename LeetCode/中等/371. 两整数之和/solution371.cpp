/*
url: https://leetcode.cn/problems/sum-of-two-integers/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution371 {
public:
    int getSum(int a, int b) {
        int carry = 0;
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int aa = (a >> i) & 1;
            int bb = (b >> i) & 1;
            res |= (aa ^ bb ^ carry) << i;
            if ((aa & bb) || ((aa | bb) & carry)) {
                carry = 1;
            }
            else carry = 0;
        }
        return res;
    }

    // 官方题解写法
    int getSum_implementation2(int a, int b) {
        // 把 b 当成进位状态来用
        while (b != 0) {
            int carry = (a & b) << 1; // 计算下一轮的进位信息，比如 101 + 001，进位为 010 (<< 1是因为进位要加到高一位)
            a = a ^ b; // 异或相当于无进位加法
            b = carry;
        }
        return a;
    }
};

int main(int argc, char const *argv[]) {
    Solution371 solu;
    cout << solu.getSum(1, 2) << endl;
    cout << solu.getSum(-167, -15) << endl;
    cout << solu.getSum(-167, 15) << endl;
    cout << solu.getSum_implementation2(1, 2) << endl;
    cout << solu.getSum_implementation2(-167, -15) << endl;
    cout << solu.getSum_implementation2(-167, 15) << endl;
    return 0;
}
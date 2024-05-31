/*
描述: 给定n，求n的所有因子
相关: LeetCode3164. 优质数对的总数 II, 典型问题/质因数分解
*/

#include <bits/stdc++.h>

using namespace std;

class AllFactor {
public:
    vector<int> allFactor(int n) {
        vector<int> factors;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                if (i * i != n) {
                    factors.push_back(i);
                    factors.push_back(n / i);
                }
                else factors.push_back(i);
            }
        }
        return factors;
    }
};

int main(int argc, char const *argv[]) {
    AllFactor af;
    auto a = af.allFactor(15);
    return 0;
}

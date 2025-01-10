// https://leetcode.cn/problems/find-the-key-of-the-numbers/?envType=daily-question&envId=2025-01-11
#include <bits/stdc++.h>

using namespace std;

class Solution3270 {
public:
    int generateKey(int num1, int num2, int num3) {
        int ans = 0;
        int w = 1;
        for (int i = 0; i < 4; i++) {
            int digit = min({num1 % 10, num2 % 10, num3 % 10});
            ans += digit * w;
            w *= 10;
            num1 /= 10;
            num2 /= 10;
            num3 /= 10;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3270 solu;
    cout << solu.generateKey(987, 879, 798) << endl;
    return 0;
}

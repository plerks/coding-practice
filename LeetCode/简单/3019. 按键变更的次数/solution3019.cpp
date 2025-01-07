// https://leetcode.cn/problems/number-of-changing-keys/?envType=daily-question&envId=2025-01-07
#include <bits/stdc++.h>

using namespace std;

class Solution3019 {
public:
    int countKeyChanges(string s) {
        int n = s.size();
        int ans = 0;
        int mask = 32;
        for (int i = 1; i < n; i++) {
            if ((s[i] | mask) != (s[i - 1] | mask)) ans++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3019 solu;
    cout << solu.countKeyChanges("aAbBcC") << endl;
    return 0;
}
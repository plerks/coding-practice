/*
url: https://leetcode.cn/problems/count-commas-in-range/
相关: LeetCode3871. 统计范围内的逗号 II 
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3870 {
public:
    int countCommas(int n) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            string s = to_string(i);
            int len = s.size();
            ans += (len - 1) / 3;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
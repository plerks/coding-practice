/*
url: https://leetcode.cn/problems/minimum-number-of-chairs-in-a-waiting-room/description/
标签: LeetCode第400场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3168 {
public:
    int minimumChairs(string s) {
        int count = 0;
        int ans = 0;
        for (char ch : s) {
            if (ch == 'E') count++;
            else count--;
            ans = max(ans, count);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

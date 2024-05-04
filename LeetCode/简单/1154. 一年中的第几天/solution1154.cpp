// https://leetcode.cn/problems/day-of-the-year/description/

#include <bits/stdc++.h>

using namespace std;

class Solution1154 {
public:
    int dayOfYear(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        int ans = 0;
        vector<int> count = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int i = 1; i < month; i++) {
            if (i == 2) {
                if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
                    ans += 29;
                }
                else ans += 28;
            }
            else {
                ans += count[i -  1];
            }
        }
        ans += day;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1154 solu;
    cout << solu.dayOfYear("2019-01-09") << endl;
    cout << solu.dayOfYear("2019-02-10") << endl;
    return 0;
}
